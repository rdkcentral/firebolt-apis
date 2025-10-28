#!/bin/bash

set -o pipefail

current_apis_dir=$PWD
current_dir=${PWD%/*}

if [[ -z $TOOL_VERSION ]]; then
  TOOL_VERSION='declare -A TOOL_VERSION=(
    [mock-firebolt]="5d32c6adf908f88c63ada603de41ffdea190eea7"
    [firebolt-certification-app]="ee2cfd1787b5f6f6ff2e716eeb4fa376c7f6643b"
    [puppeteer]="24.17.0"
    [mochawesome-report-generator]="6.2.0"
  )'
fi
eval "$TOOL_VERSION"
echo "Dependencies taken from the following versions" >/dev/stderr
for i in ${!TOOL_VERSION[*]}; do
  echo "- $i: ${TOOL_VERSION[$i]}"
done | sort >/dev/stderr
echo >/dev/stderr

# Function to check if a branch exists in the remote repository
function branch_exists() {
    local branch=$1
    git ls-remote --heads https://github.com/rdkcentral/firebolt-apis.git "$branch" | grep -q "$branch"
}

function add_ts() {
  local prefix=$1 start=$((${EPOCHREALTIME/[,.]}/1000)) delta= l=
  cat - | while read -r l; do
    delta=$((${EPOCHREALTIME/[,.]}/1000 - start))
    printf "%-5s: %3d.%03d: %s\n" "$prefix" "$((delta/1000))" "$((delta%1000))" "$l"
  done
}

function clean_ansi() {
  sed -u -e 's/\x1b\[[0-9;]\+[mMGK]//g' -e 's/\x1b\[[Jm]//g'
}

function runTests(){
  echo "Determine the branch to checkout"
  # Convert event name to lowercase
  PR_BRANCH="${EVENT_NAME,,}"

  # Check if OPENRPC_PR_BRANCH is not empty and the event is repository_dispatch
  if [ -n "$OPENRPC_PR_BRANCH" ] && [ "$PR_BRANCH" == "repository_dispatch" ]; then
      # Check if the branch exists in firebolt-apis
      if branch_exists "$OPENRPC_PR_BRANCH"; then
          PR_BRANCH=$OPENRPC_PR_BRANCH
          echo "Using branch from OPENRPC_PR_BRANCH: $OPENRPC_PR_BRANCH"
      else
          echo "Branch '$OPENRPC_PR_BRANCH' does not exist in firebolt-apis. Defaulting to 'next'."
          PR_BRANCH="next"
      fi
  elif [ "$PR_BRANCH" == "pull_request" ]; then
      # If it's a pull request event, use the PR branch
      PR_BRANCH=$PR_HEAD_REF
  elif [ "$PR_BRANCH" == "push" ]; then
      # For push events, extract the branch name
      PR_BRANCH=$GITHUB_REF
      PR_BRANCH="${PR_BRANCH#refs/heads/}"
  else
      echo "Unsupported event: $EVENT_NAME"
      exit 1
  fi

  cd $current_dir
  if [[ ! -e firebolt-apis ]]; then
    echo "Cloning firebolt-apis repo with branch: $PR_BRANCH"
    git clone --branch $PR_BRANCH https://github.com/rdkcentral/firebolt-apis.git
  fi
  echo "Cd to firebolt-apis repo and compile firebolt-open-rpc.json"
  cd firebolt-apis
  if [ "$EVENT_NAME" == "repository_dispatch" ]; then
  # If OPENRPC_PR_BRANCH is set and is not 'next'
    if [ -n "$OPENRPC_PR_BRANCH" ] && [ "$OPENRPC_PR_BRANCH" != "next" ]; then
      echo "Updating OpenRPC dependency to branch: $OPENRPC_PR_BRANCH"
      jq ".dependencies[\"@firebolt-js/openrpc\"] = \"file:../firebolt-openrpc#$OPENRPC_PR_BRANCH\"" package.json > package.json.tmp && mv package.json.tmp package.json
    fi
  fi
  npm i
  npm run compile
  npm run dist

  cd $current_dir
  echo "Clone mfos repo and start it in the background"
  git clone --depth 1 --branch main https://github.com/rdkcentral/mock-firebolt.git
  cd mock-firebolt
  git fetch --shallow-since=2025-01-01
  git reset --hard ${TOOL_VERSION[mock-firebolt]}
  cd server
  cp $current_apis_dir/dist/firebolt-open-rpc.json src/firebolt-open-rpc.json
  cat src/.mf.config.SAMPLE.json \
  | jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' \
  | jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' \
  > src/.mf.config.json
  npm install
  npm start |& add_ts "MFOS" | tee >(clean_ansi >$current_dir/log-mfos.log) &

  cd $current_dir
  echo "Clone fca repo and start it in the background"
  git clone --depth 1 --branch main https://github.com/rdkcentral/firebolt-certification-app.git
  cd firebolt-certification-app
  git fetch --shallow-since=2025-01-01
  git reset --hard ${TOOL_VERSION[firebolt-certification-app]}
  cat package.json \
  | jq '.dependencies["@firebolt-js/sdk"] = "file:'"$current_apis_dir"'/src/sdks/core"' \
  > package.json.tmp && mv package.json.tmp package.json
  npm install
  # npm start 2>&1 | grep -v "Error:.*Cannot find module.*/plugins/" &
  npm start |& add_ts "FCA" | tee >(clean_ansi >$current_dir/log-fca.log) &
  sleep 15

  cd $current_dir
  echo "Curl request with runTest install on initialization: $(curl -s -X POST -H "Content-Type: application/json" -d "$INTENT" http://localhost:3333/api/v1/state/method/parameters.initialization/result)"

  echo "Run mfos tests in a headless browser"
  npm install puppeteer@24.17.0
  echo "Start xvfb"
  export DISPLAY=":99"
  Xvfb $DISPLAY -screen 0 1024x768x24 > /dev/null 2>&1 &

  echo "Run headless browser script with puppeteer"
  node -e '
    const puppeteer = require("puppeteer");
    const fs = require("fs");
    (async () => {
      const browser = await puppeteer.launch({ headless: true, args: ["--no-sandbox"]});
      const page = await browser.newPage();

      // Enable console logging
      page
        .on("console", (msg) => {
          const logMessage = `${msg.text()}`;
          console.log(`NODE : ${msg.type().substr(0, 3).toUpperCase()}: ${logMessage}`);
          if (msg.type().includes("log") && logMessage.includes("Response String:")) {
            const jsonStringMatch = logMessage.match(/Response String:(.*)/);
            if (jsonStringMatch && jsonStringMatch[1]) {
              try {
                const jsonString = jsonStringMatch[1].trim();
                const responseString = JSON.parse(jsonString);
                console.log("Parsed JSON:", responseString);
                const filePath="report.json"
                fs.writeFileSync(filePath, JSON.stringify(responseString), "utf-8");
                console.log(`Parsed JSON written to ${filePath}`);
                // Exit the Node.js script
                console.log("Exiting");
                process.exit(0);
              } catch (error) {
                console.error("Error parsing JSON:", error);
              }
            }
          }
        })
      .on("pageerror", ({ message }) => console.log(`NOPE : ${message}`))
      .on("response", response => console.log(`NORE : ${response.status()} ${response.url()}`))
      .on("requestfailed", request => console.log(`NORF : ${request.failure().errorText} ${request.url()}`));
      // Navigate to the URL
      const url = "http://localhost:8081/index.html?mf=ws://localhost:9998/12345&standalone=true";
      const timeout = 120;
      console.log(`Navigating to ${url} and waiting ${timeout}s to finish`);
      await page.goto(url);

      // Sleep for "timeout" seconds
      await new Promise(resolve => setTimeout(resolve, timeout * 1000));

      // Close the browser
      console.log("Closing the browser after timeout");
      await browser.close();
    })();
  '
  [[ -e report.json ]] || { echo "Report not created"; exit 1; }
  echo "Create html and json assets"
  npm install mochawesome-report-generator@6.2.0
  local report_dir="$current_apis_dir/report"
  mkdir $report_dir
  cat report.json \
  | jq -r '.' \
  | jq '.report' \
  > $report_dir/report.json
  node -e '
    const marge = require("mochawesome-report-generator/bin/cli-main");
    marge({
      _: ["'"$report_dir"'/report.json"],
      reportFileName: "report.json",
      reportTitle: "FireboltCertificationTestReport",
      reportPageTitle: "FireboltCertificationTestReport",
      reportDir: "'"$report_dir"'",
    });
  '
  echo "Storing MFOS & FCA logs together with the report"
  cp $current_dir/log-mfos.log $current_dir/log-fca.log $report_dir
  gzip $report_dir/log-mfos.log $report_dir/log-fca.log
}

function getResults(){
  local failures=999
  [[ -e $current_apis_dir/report/report.json ]] && failures=$(jq -r '.stats.failures' $current_apis_dir/report/report.json)
  echo "If failures more than 0, fail the job, failures=$failures"
  if [[ "$failures" -eq 0 ]]; then
    echo "No failures detected."
  else
    exit 1
  fi
}

function getArtifactData(){
  PREVIOUS_JOB_ID=$(jq -r '.id' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "PREVIOUS_JOB_ID=$PREVIOUS_JOB_ID" >> "$GITHUB_ENV"
  SUITE_ID=$(jq -r '.check_suite_id' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "SUITE_ID=$SUITE_ID" >> "$GITHUB_ENV"
  ARTIFACT_ID=$(gh api "/repos/$OWNER/$REPO/actions/artifacts" --jq ".artifacts[] | select(.workflow_run.id==$PREVIOUS_JOB_ID and .expired==false) | .id") && echo "ARTIFACT_ID=$ARTIFACT_ID" >> "$GITHUB_ENV"
  PR_NUMBER=$(jq -r '.pull_requests[0].number' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "PR_NUMBER=$PR_NUMBER" >> "$GITHUB_ENV"
  ARTIFACT_URL="$SERVER_URL/$GITHUB_REPO/suites/$SUITE_ID/artifacts/$ARTIFACT_ID" && echo "ARTIFACT_URL=$ARTIFACT_URL" >> "$GITHUB_ENV"
  JOB_PATH="$SERVER_URL/$GITHUB_REPO/actions/runs/$PREVIOUS_JOB_ID" && echo "JOB_PATH=$JOB_PATH" >> "$GITHUB_ENV"
}

function unzipArtifact(){
  unzip report.zip
  # Extract values from report.json
  report=$(cat report.json | jq -r '.')
  passes=$(echo "$report" | jq -r '.stats.passes')
  failures=$(echo "$report" | jq -r '.stats.failures')
  pending=$(echo "$report" | jq -r '.stats.pending')
  skipped=$(echo "$report" | jq -r '.stats.skipped')
  echo "Skipped=$skipped" >> "$GITHUB_ENV"
  echo "Pending=$pending" >> "$GITHUB_ENV"
  echo "Passes=$passes" >> "$GITHUB_ENV"
  echo "Failures=$failures" >> "$GITHUB_ENV"
}


# Check argument and call corresponding function
case "$1" in
runTests) runTests;;
getResults) getResults;;
getArtifactData) getArtifactData;;
unzipArtifact) unzipArtifact;;
*) echo "Invalid function specified." exit 1;;
esac
