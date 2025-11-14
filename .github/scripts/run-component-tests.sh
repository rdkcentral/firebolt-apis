#!/usr/bin/env bash
# vim: ts=4

set -eu

die() {
    echo "$@" >/dev/stderr
    exit 1
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

specOpenRpc=
specAppOpenRpc=
mockPath=
mockConfig=
mockPort=9998
testExe=

while [[ ! -z ${1:-} ]]; do
    case $1 in
    --mock) mockPath="$2"; shift;;
    --port) mockPort="$2"; shift;;
    --config) mockConfig="$2"; shift;;
    --openrpc) specOpenRpc="$2"; shift;;
    --app-openrpc) specAppOpenRpc="$2"; shift;;
    --test-exe) testExe="$2"; shift;;
    *) break;;
    esac; shift
done

[[ -e $mockPath ]] || die "mock-firebolt not installed"
[[ -e $specOpenRpc ]] || die "OpenRPC spec '$specOpenRpc' not found"
[[ -e $specAppOpenRpc ]] || die "OpenRPC App spec '$specOpenRpc' not found"
[[ -e $mockConfig ]] || die "Config '$mockConfig' not found"
[[ -e $testExe ]] || die "Executable for CT '$testExe' not found"

cfgFile=$mockPath/server/src/.mf.config.json

echo "Updating config for mock, $cfgFile"
jq '
  (.supportedOpenRPCs[] | select(.name=="core")).fileName = "'"$specOpenRpc"'"
  | (.supportedToAppOpenRPCs[] | select(.name=="coreToApp")).fileName = "'"$specAppOpenRpc"'"
' \
  $mockConfig > $cfgFile

echo "Starting mock-server, $mockPath/server"
cd $mockPath/server
npm start &
mock_pid=$!
echo "Mock started at pid: $mock_pid"

sleep 1
try=0
maxTries=10
while ! nc -z localhost $mockPort >/dev/null 2>&1; do
  (( try < maxTries )) || die "Mock server not ready after $try tries"
  (( ++try ))
  printf "%d/%d Waiting for mock-server to be up&ready\n" $try $maxTries
  sleep 1
done

echo "Starting Component Tests"
cd $(dirname $testExe)
"./$(basename $testExe)"
exitCode=$?

kill-rec $mock_pid

exit $exitCode
