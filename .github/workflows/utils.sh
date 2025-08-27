#!/bin/bash
set -o pipefail

current_apis_dir=$PWD
current_dir=${PWD%/*}

echo "current_apis_dir='$current_apis_dir'" >/dev/stderr
echo "current_dir='$current_dir'" >/dev/stderr

if [[ -z $GIT_REPOS_VERSIONS ]]; then
  GIT_REPOS_VERSIONS='declare -A GIT_REPOS_VERSIONS=(
    [mock-firebolt]="5d32c6adf908f88c63ada603de41ffdea190eea7"
    [firebolt-certification-app]="30c96d4dfb601897fcb557e5f0a6225402df8964"
    [nlohmann]="v3.11.3"
    [json-schema-validator]="2.3.0"
    [google-test]="v1.15.2"
    [firebolt-native-transport]="main"
    [thunder]="283b3d54334010403d85a4e69b3835de23e42331"
    [thunder-tools]="64b72b5ed491436b0e6bc2327d8a7b0e75ee2870"
  )'
fi
eval "$GIT_REPOS_VERSIONS"
echo "Dependencies taken from the following versions" >/dev/stderr
for i in ${!GIT_REPOS_VERSIONS[*]}; do
  echo "- $i: ${GIT_REPOS_VERSIONS[$i]}"
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
  git reset --hard ${GIT_REPOS_VERSIONS[mock-firebolt]}
  cd server
  cp $current_apis_dir/dist/firebolt-open-rpc.json src/firebolt-open-rpc.json
  cat src/.mf.config.SAMPLE.json \
  | jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' \
  | jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' \
  > src/.mf.config.json
  npm install
  npm start |& add_ts "MFOS" | tee >(clean_ansi >log-mfos.log) &

  cd $current_dir
  echo "Clone fca repo and start it in the background"
  git clone --depth 1 --branch main https://github.com/rdkcentral/firebolt-certification-app.git
  cd firebolt-certification-app
  git fetch --shallow-since=2025-01-01
  git reset --hard ${GIT_REPOS_VERSIONS[firebolt-certification-app]}
  cat package.json \
  | jq '.dependencies["@firebolt-js/sdk"] = "file:'"$current_apis_dir"'/src/sdks/core"' \
  > package.json.tmp && mv package.json.tmp package.json
  npm install
  # npm start 2>&1 | grep -v "Error:.*Cannot find module.*/plugins/" &
  npm start |& add_ts "FCA" | tee >(clean_ansi >log-fca.log) &
  sleep 15

  cd $current_dir
  echo "Curl request with runTest install on initialization: $(curl -s -X POST -H "Content-Type: application/json" -d "$INTENT" http://localhost:3333/api/v1/state/method/parameters.initialization/result)"

  echo "Run mfos tests in a headless browser"
  npm install puppeteer
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
  npm i mochawesome-report-generator
  mkdir report
  mv report.json report/
  echo "rt: pwd:$PWD, reports/: $(ls report/)"
  jq -r '.' report/report.json > tmp.json && mv tmp.json report/report.json
  jq '.report' report/report.json > tmp.json && mv tmp.json report/report.json
  node -e '
    const marge = require("mochawesome-report-generator/bin/cli-main");
    marge({
      _: ["report/report.json"],
      reportFileName: "report.json",
      reportTitle: "FireboltCertificationTestReport",
      reportPageTitle: "FireboltCertificationTestReport",
      reportDir: "./report",
    });
  '
}

function getResults(){
  echo "gr: pwd:$PWD, reports/: $(ls report/)"
  local failures=999
  [[ -e report/report.json ]] && failures=$(cat report/report.json | jq -r '.stats.failures')
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

function cloneAndInstallDeps() {
  echo " ************ Installing dependencies ************ (should be preinstalled in docker image)"

  cd $current_dir
  rm -rf nlohmann-json json-schema-validator googletest

  git clone --depth 1 --branch ${GIT_REPOS_VERSIONS[nlohmann]} https://github.com/nlohmann/json nlohmann-json \
  || { echo "deps: nlohmann-json: cloning failed"; exit 1; }

  git clone --depth 1 --branch ${GIT_REPOS_VERSIONS[json-schema-validator]} https://github.com/pboettch/json-schema-validator.git \
  || { echo "deps: json-schema-validator: cloning failed"; exit 1; }

  git clone --depth 1 --branch ${GIT_REPOS_VERSIONS[google-test]} https://github.com/google/googletest \
  || { echo "deps: googletest: cloning failed"; exit 1; }

  echo "deps: building"

  local i=
  for i in nlohmann-json json-schema-validator googletest; do
    rm -rf build/$i
    cmake -S $i -B build/$i \
      -DCMAKE_INSTALL_PREFIX:PATH=$current_dir/install/usr -DBUILD_SHARED_LIBS=ON \
    || { echo "deps: $i: cmake init failed"; exit 1; }
    cmake --build build/$i --target install \
    || { echo "deps: $i: building failed"; exit 1; }
  done
  echo "deps: building succeeded"
}

function cloneAndInstallTransport() {
  echo " ************ Cloning Tranport ************"

  cd $current_dir

  rm -rf firebolt-native-transport
  git clone --depth 1 --branch ${GIT_REPOS_VERSIONS[firebolt-native-transport]} https://github.com/rdkcentral/firebolt-native-transport.git \
  || { echo "firebolt-native-transport: cloning failed"; exit 1; }

  rm -rf build/firebolt-native-transport

  echo "firebolt-native-transport: building"

  cmake -S firebolt-native-transport -B build/firebolt-native-transport \
    -DSYSROOT_PATH=$current_dir/install -DCMAKE_INSTALL_PREFIX="$current_dir/install/usr" \
    -DENABLE_UNIT_TESTS=ON \
  || { echo "firebolt-native-transport: cmake init failed"; exit 1; }
  cmake --build build/firebolt-native-transport --target install \
  || { echo "firebolt-native-transport: building failed"; exit 1; }

  echo "firebolt-native-transport: building succeeded"
}

function cloneAndInstallThunder() {
  echo " ************ Cloning Thunder & ThunderTools ************ (should be preinstalled in docker image)"
  cd $current_dir

  rm -rf Thunder
  git clone --depth 1 --branch R5.0.0 https://github.com/rdkcentral/Thunder.git \
  || { echo "thunder: cloning failed"; exit 1; }
  (
    cd Thunder \
    && git fetch --shallow-since=2024-05-20 \
    && git reset --hard ${GIT_REPOS_VERSIONS[thunder]}
  ) || { echo "thunder: checking out failed"; exit 1; }

  rm -rf ThunderTools
  git clone --depth 1 --branch R5.0.0 https://github.com/rdkcentral/ThunderTools.git \
  || { echo "thunder-tools: cloning failed"; exit 1; }
  (
    cd ThunderTools \
    && git fetch --shallow-since=2024-05-20 \
    && git reset --hard ${GIT_REPOS_VERSIONS[thunder-tools]}
  ) || { echo "thunder-tools: checking out failed"; exit 1; }

  rm -rf build/Thunder build/ThunderTools

  echo "thunder-tools: building"

  cmake -G Ninja -S ThunderTools -B build/ThunderTools -DCMAKE_INSTALL_PREFIX="install/usr" && echo "Tools Setup" \
  || { echo "thunder-tools: cmake init failed"; exit 1; }

  cmake --build build/ThunderTools --target install && echo "Thunder Tools Build succeeded" \
  || { echo "thunder-tools: building failed"; exit 1; }

  echo "thunder: building"

  #-G Ninja is the "Build system generator"
  #-S is the source path
  #-B is the output directory
  cmake -G Ninja -S Thunder -B build/Thunder \
    -DBUILD_SHARED_LIBS=ON \
    -DBINDING="127.0.0.1" \
    -DCMAKE_BUILD_TYPE="Debug" \
    -DCMAKE_INSTALL_PREFIX="install/usr" \
    -DCMAKE_MODULE_PATH="$PWD/install/usr/include/WPEFramework/Modules" \
    -DDATA_PATH="$PWD/install/usr/share/WPEFramework" \
    -DPERSISTENT_PATH="$PWD/install/var/wpeframework" \
    -DPORT="55555" \
    -DPROXYSTUB_PATH="$PWD/install/usr/lib/wpeframework/proxystubs" \
    -DSYSTEM_PATH="$PWD/install/usr/lib/wpeframework/plugins" \
    -DVOLATILE_PATH="tmp" && echo "Thunder configure succeeded" \
  || { echo "thunder: cmake init failed"; exit 1; }

  cmake --build build/Thunder --target install && echo "Thunder Build succeeded" \
  || { echo "thunder: building failed"; exit 1; }
}

function buildRuntimeCoreSDK() {
  echo " ************ Building Runtime APIs Core SDK ************"

  cd $current_apis_dir
  FIREBOLT_VERSION=$(node -p "require('./package.json').version")

  echo "core-sdk: the version from package.json is $FIREBOLT_VERSION"

  local tarSDK="firebolt-apis--core-sdk-$FIREBOLT_VERSION.tar.gz"
  echo "core-sdk: $tarSDK"

  rm -rf ./$tarSDK $current_dir/verif

  git config --global --add safe.directory /__w/firebolt-apis/firebolt-apis
  git archive -v --format=tar.gz --prefix=firebolt-apis/ -o $tarSDK HEAD src/cpp \
  || { echo "core-sdk: cannot make SDK archive"; exit 1; }

  echo "core-sdk: sha256sum-sdk  : $(sha256sum $tarSDK)"

  cd $current_dir
  mkdir $current_dir/verif
  tar -C $current_dir/verif -zxf $current_apis_dir/$tarSDK

  rm -rf build/firebolt-apis

  echo "core-sdk: building"

  export LD_LIBRARY_PATH="$current_dir/install/usr/lib:$LD_LIBRARY_PATH"
  cmake -S verif/firebolt-apis/src/cpp -B build/firebolt-apis \
    -DSYSROOT_PATH=$current_dir/install -DCMAKE_INSTALL_PREFIX="$current_dir/install/usr" \
    -DENABLE_UNIT_TESTS=ON \
  || { echo "core-sdk: cmake init failed"; exit 1; }
  cmake --build build/firebolt-apis \
  || { echo "core-sdk: building failed"; exit 1; }

  THROW_ERROR_ON_UT_FAIL=${THROW_ERROR_ON_UT_FAIL:-false}
  cp firebolt-apis/src/cpp/firebolt-core-open-rpc.json ./
  ln -s firebolt-core-open-rpc.json firebolt-open-rpc.json
  if ! ./build/firebolt-apis/test/FireboltCoreUnitTests; then
    echo "core-sdk: UT verification failed"
    if $THROW_ERROR_ON_UT_FAIL; then
      exit 1
    else
      echo "core-sdk: error not signaled"
    fi
  fi
}

# Check argument and call corresponding function
case "$1" in
runTests) runTests;;
getResults) getResults;;
getArtifactData) getArtifactData;;
unzipArtifact) unzipArtifact;;
cloneAndInstallDeps) cloneAndInstallDeps;;
cloneAndInstallThunder) cloneAndInstallThunder;;
cloneAndInstallTransport) cloneAndInstallTransport;;
buildRuntimeCoreSDK) buildRuntimeCoreSDK;;
*) echo "Invalid function specified." exit 1;;
esac
