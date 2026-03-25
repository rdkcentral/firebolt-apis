#!/bin/bash

set -o pipefail

current_apis_dir=$PWD
current_dir=${PWD%/*}

declare -A TOOL_VERSION=(
  [mock-firebolt]="5d32c6adf908f88c63ada603de41ffdea190eea7"
  [firebolt-certification-app]="ee2cfd1787b5f6f6ff2e716eeb4fa376c7f6643b"
  [puppeteer]="24.17.0"
  [mochawesome-report-generator]="6.2.0")

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

add_ts() {
  local prefix=$1 start=$((${EPOCHREALTIME/[,.]}/1000)) delta= l=
  cat - | while read -r l; do
    delta=$((${EPOCHREALTIME/[,.]}/1000 - start))
    printf "%-5s: %3d.%03d: %s\n" "$prefix" "$((delta/1000))" "$((delta%1000))" "$l"
  done
}

clean_ansi() {
  sed -u -e 's/\x1b\[[0-9;]\+[mMGK]//g' -e 's/\x1b\[[Jm]//g'
}

kill-rec() {
  local pid="$1" i= children=
  if children="$(pgrep -P "$pid")"; then
    for i in $children; do
      kill-rec $i
    done
  fi
  kill -9 "$pid"
}

run_mfos_tests()
{
  cd $current_dir
  echo "Run mfos tests in a headless browser"
  PUPPETEER_SKIP_DOWNLOAD=1 npm install puppeteer@${TOOL_VERSION[puppeteer]}
  if [ -z "${PUPPETEER_EXECUTABLE_PATH:-}" ]; then
    echo "ERROR: PUPPETEER_EXECUTABLE_PATH is not set. Set it to the path of your Chrome/Chromium binary (e.g. /usr/bin/google-chrome-stable)." >&2
    exit 1
  fi
  echo "Start xvfb"
  export DISPLAY=":99"
  Xvfb $DISPLAY -screen 0 1024x768x24 |& add_ts "XVFB" | tee >(clean_ansi >$current_dir/log-xvfb.log) >/dev/null 2>&1 &
  local xvfb_pid
  xvfb_pid=$(pgrep -n -x Xvfb 2>/dev/null || true)
  # Wait for Xvfb to be ready before launching Chrome (non-fatal: headless Chrome
  # does not require a real display, so we proceed even if xdpyinfo never connects).
  for i in $(seq 1 10); do xdpyinfo -display :99 >/dev/null 2>&1 && break; sleep 1; done

  echo "Run headless browser script with puppeteer"
  node -e '
    const puppeteer = require("puppeteer");
    const fs = require("fs");
    (async () => {
      const browser = await puppeteer.launch({
        headless: true,
        executablePath: process.env.PUPPETEER_EXECUTABLE_PATH,
        args: [
          "--no-sandbox",
          "--disable-dev-shm-usage",
          "--enable-webgl",
          "--enable-unsafe-swiftshader",
          "--ignore-gpu-blocklist",
        ]
      });
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
      // Navigate to the URL - retry up to 12 times (60s window) so a
      // slow-starting webpack-dev-server does not abort the test immediately.
      const url = "http://localhost:8081/index.html?mf=ws://localhost:9998/12345&standalone=true";
      const timeout = 300;
      const maxRetries = 12;
      let navigated = false;
      for (let attempt = 0; attempt < maxRetries; attempt++) {
        try {
          console.log(`Navigation attempt ${attempt + 1}/${maxRetries} to ${url}`);
          await page.goto(url, { timeout: 10000, waitUntil: "domcontentloaded" });
          navigated = true;
          break;
        } catch (err) {
          console.log(`Navigation attempt ${attempt + 1} failed: ${err.message}. Retrying in 5s...`);
          await new Promise(r => setTimeout(r, 5000));
        }
      }
      if (!navigated) {
        console.error("Failed to navigate to FCA after all retry attempts");
        await browser.close();
        process.exit(1);
      }
      console.log(`Successfully navigated to FCA. Waiting up to ${timeout}s for test results...`);

      // Sleep for "timeout" seconds
      await new Promise(resolve => setTimeout(resolve, timeout * 1000));

      // Close the browser
      console.log("Closing the browser after timeout");
      await browser.close();
    })();
  '
  [ -n "$xvfb_pid" ] && kill-rec "$xvfb_pid" 2>/dev/null || true
}


runTests() {
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

  echo "compile firebolt-open-rpc.json"
  npm i
  npm run compile
  npm run dist

  cd $current_dir
  if [[ ! -e mock-firebolt ]]; then
    echo "Clone mfos repo and start it in the background"
    git clone --depth 1 --branch main https://github.com/rdkcentral/mock-firebolt.git
    cd mock-firebolt
    git fetch --shallow-since=2025-01-01
    git checkout ${TOOL_VERSION[mock-firebolt]}
  fi

  cd $current_dir
  if [[ ! -e firebolt-certification-app ]]; then
    echo "Clone fca repo and start it in the background"
    git clone --depth 1 --branch main https://github.com/rdkcentral/firebolt-certification-app.git
    cd firebolt-certification-app
    git fetch --shallow-since=2025-01-01
    git checkout ${TOOL_VERSION[firebolt-certification-app]}
    echo "Applying dependency patch: $current_apis_dir/.github/fca/dependency.patch"
    if ! git apply "$current_apis_dir/.github/fca/dependency.patch"; then
      echo "ERROR: Failed to apply dependency patch" >&2
      exit 1
    fi
    echo "Applying webpack patch: $current_apis_dir/.github/fca/webpack.patch"
    if ! git apply "$current_apis_dir/.github/fca/webpack.patch"; then
      echo "ERROR: Failed to apply webpack patch" >&2
      exit 1
    fi
  fi

  echo "starting mfos"
  cd $current_dir/mock-firebolt/server
  cp $current_apis_dir/dist/firebolt-open-rpc.json src/firebolt-open-rpc.json
  cat src/.mf.config.SAMPLE.json \
  | jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' \
  | jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' \
  > src/.mf.config.json
  npm install
  npm start |& add_ts "MFOS" | tee >(clean_ansi >$current_dir/log-mfos.log) &
  mfos_pid=$!

  echo "starting fca"
  cd $current_dir/firebolt-certification-app
  cat package.json \
  | jq '.dependencies["@firebolt-js/sdk"] = "file:'"$current_apis_dir"'/src/sdks/core"' \
  > package.json.tmp && mv package.json.tmp package.json
  npm install --legacy-peer-deps
  npm start  |& add_ts "FCA" | tee >(clean_ansi >$current_dir/log-fca.log) &
  fca_pid=$!

  # Wait for MFOS REST API (port 3333) to be ready before setting intent
  echo "Waiting for MFOS to be ready on port 3333..."
  mfos_up=0
  for i in $(seq 1 60); do
    if curl -s --max-time 2 http://localhost:3333/ > /dev/null 2>&1; then
      mfos_up=1
      break
    fi
    sleep 1
  done
  [ "$mfos_up" -eq 1 ] || { echo "ERROR: MFOS did not come up on port 3333 within 60s" >&2; exit 1; }

  cd $current_dir
  CURL_RESP=$(curl -s -X POST -H "Content-Type: application/json" -d "$INTENT" http://localhost:3333/api/v1/state/method/parameters.initialization/result)
  echo "Curl request with runTest install on initialization: $CURL_RESP"
  # Fail fast if MFOS rejected the intent (empty INTENT, wrong format, or non-JSON error response)
  MFOS_STATUS=$(echo "$CURL_RESP" | jq -r '.status' 2>/dev/null)
  if [ $? -ne 0 ]; then
    echo "ERROR: Failed to parse MFOS response as JSON while validating initialization intent."
    echo "Received: $CURL_RESP"
    exit 1
  fi
  if [ "$MFOS_STATUS" != "SUCCESS" ]; then
    echo "ERROR: MFOS rejected initialization intent (status=$MFOS_STATUS). Check INTENT variable format."
    echo "Received: $CURL_RESP"
    exit 1
  fi

  # Wait for FCA's webpack bundle to finish compiling before launching puppeteer.
  # webpack-dev-server v3 prints either "Compiled successfully." (no warnings)
  # or "Compiled with warnings." - we match both.
  echo "Waiting for FCA webpack-dev-server to finish compiling (up to 300s)..."
  fca_compiled=0
  for i in $(seq 1 300); do
    if grep -qi "compiled successfully\|compiled with warnings" "$current_dir/log-fca.log" 2>/dev/null; then
      fca_compiled=1
      echo "FCA webpack compiled after ${i}s. Last FCA log lines:"
      tail -5 "$current_dir/log-fca.log" | head -5 || true
      break
    fi
    sleep 1
  done
  if [ "$fca_compiled" -eq 0 ]; then
    echo "WARNING: FCA webpack did not report successful compilation within 300s. Proceeding anyway (may fail)." >&2
    echo "--- last 30 lines of FCA log ---" >&2
    tail -30 "$current_dir/log-fca.log" >&2 2>/dev/null || true
  fi

  run_mfos_tests

  kill-rec $mfos_pid
  kill-rec $fca_pid

  cd $current_dir
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

getResults() {
  local failures=999
  [[ -e $current_apis_dir/report/report.json ]] && failures=$(jq -r '.stats.failures' $current_apis_dir/report/report.json)
  echo "If failures more than 0, fail the job, failures=$failures"
  if [[ "$failures" -eq 0 ]]; then
    echo "No failures detected."
  else
    exit 1
  fi
}

getArtifactData() {
  PREVIOUS_JOB_ID=$(jq -r '.id' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "PREVIOUS_JOB_ID=$PREVIOUS_JOB_ID" >> "$GITHUB_ENV"
  SUITE_ID=$(jq -r '.check_suite_id' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "SUITE_ID=$SUITE_ID" >> "$GITHUB_ENV"
  ARTIFACT_ID=$(gh api "/repos/$OWNER/$REPO/actions/artifacts" --jq ".artifacts[] | select(.workflow_run.id==$PREVIOUS_JOB_ID and .expired==false) | .id") && echo "ARTIFACT_ID=$ARTIFACT_ID" >> "$GITHUB_ENV"
  PR_NUMBER=$(jq -r '.pull_requests[0].number' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "PR_NUMBER=$PR_NUMBER" >> "$GITHUB_ENV"
  ARTIFACT_URL="$SERVER_URL/$GITHUB_REPO/suites/$SUITE_ID/artifacts/$ARTIFACT_ID" && echo "ARTIFACT_URL=$ARTIFACT_URL" >> "$GITHUB_ENV"
  JOB_PATH="$SERVER_URL/$GITHUB_REPO/actions/runs/$PREVIOUS_JOB_ID" && echo "JOB_PATH=$JOB_PATH" >> "$GITHUB_ENV"
}

unzipArtifact() {
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
