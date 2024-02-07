#!/bin/bash
set -o pipefail

echo "Clone firebolt-apis repo with pr branch"
PR_BRANCH=$(echo "$EVENT_NAME" | tr '[:upper:]' '[:lower:]')
if [ "${PR_BRANCH}" == "pull_request" ]; then
  PR_BRANCH=$PR_HEAD_REF
elif [ "${PR_BRANCH}" == "push" ]; then
  PR_BRANCH=$GITHUB_REF
  PR_BRANCH="${PR_BRANCH#refs/heads/}"
else
  echo "Unsupported event: $EVENT_NAME"
  exit 1
fi

git clone --branch ${PR_BRANCH} https://github.com/rdkcentral/firebolt-apis.git
echo "cd to firebolt-apis repo and compile firebolt-open-rpc.json"
cd firebolt-apis
npm i
npm run compile
npm run dist
cd ..

echo "clone mfos repo and start it in the background"
git clone https://github.com/rdkcentral/mock-firebolt.git
cd mock-firebolt/server
cp ../../firebolt-apis/dist/firebolt-open-rpc.json ../../mock-firebolt/server/src/firebolt-open-rpc.json
jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
cp src/.mf.config.SAMPLE.json src/.mf.config.json
npm install
npm start &
cd ..//..

echo "clone fca repo and start it in the background"
git clone https://github.com/rdkcentral/firebolt-certification-app.git
cd firebolt-certification-app
jq '.dependencies["@firebolt-js/sdk"] = "file:../firebolt-apis/src/sdks/core"' package.json > package.json.tmp && mv package.json.tmp package.json
cat package.json
npm install
npm start &
sleep 5s
cd ..

echo "curl request with runTest install on initialization"
response=$(curl -X POST -H "Content-Type: application/json" -d '{
  "result": {
    "lmt": 0,
    "us_privacy": "1-N-",
    "discovery": {
      "navigateTo": {
        "action": "search",
        "data": {
          "query": "{\"task\":\"runTest\",\"params\":{\"certification\":true,\"exceptionMethods\":[],\"methodsToBeExcluded\":[]},\"action\":\"CORE\",\"context\":{\"communicationMode\":\"SDK\"},\"metadata\":{\"target\":\"MFOS\",\"targetVersion\":\"NIL\",\"deviceModel\":\"NIL\",\"fbVersion\":\"NA\"},\"asynchronous\":false,\"appType\":\"firebolt\"}"
        },
        "context": {
          "source": "voice"
        }
      }
    }
  }
}' http://localhost:3333/api/v1/state/method/parameters.initialization/result)

echo "run mfos tests in a headless browser"
npm install puppeteer
echo "Start xvfb"
Xvfb :99 -screen 0 1024x768x24 > /dev/null 2>&1 &
export DISPLAY=:99

echo "Run headless browser script with puppeteer"
node -e '
  const puppeteer = require("puppeteer");
  const fs = require("fs");
  (async () => {
    const browser = await puppeteer.launch({ headless: true, args: ["--no-sandbox", "--disable-gpu"] });
    const page = await browser.newPage();

    // Enable console logging
    page.on("console", (msg) => {
    let logMessage="";
    if (msg.type().includes("log")) {
     logMessage = `${msg.text()}`;
     console.log(logMessage);
    }
   if (logMessage.includes("Response String:")) {
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
          process.exit(0);

        } catch (error) {
          console.error("Error parsing JSON:", error);
        }
      }
    }
  });
    // Navigate to the URL
    await page.goto("http://localhost:8081/?mf=ws://localhost:9998/12345&standalone=true");

   // Sleep for 80 seconds (80,000 milliseconds)
   await new Promise(resolve => setTimeout(resolve, 80000));

    // Close the browser
    await browser.close();
  })();
'
echo "create html and json assets"
npm i mochawesome-report-generator
mkdir report
mv report.json report/
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