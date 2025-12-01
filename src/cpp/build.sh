#!/usr/bin/env bash

set -e

bdir="build"
do_install=false
params=
buildType="Debug"

while [[ ! -z $1 ]]; do
  case $1 in
  --clean) rm -rf $bdir;;
  --release) buildTarget="Release";;
  --sysroot) SYSROOT_PATH="$2"; shift;;
  -i | --install) do_install=true;;
  +tests) params+=" -DENABLE_TESTS=ON";;
  +demo)  params+=" -DENABLE_DEMO_APP=ON";;
  +gen-cov)
    set -e
    cd build
    cp ../firebolt-open-rpc.json ./test/
    ctest --test-dir ./test
    mkdir -p coverage
    gcovr -r .. \
      --gcov-exclude-directory 'test' \
      --medium-threshold 50 --high-threshold 75 \
      --html-details coverage/index.html \
      --cobertura coverage.cobertura.xml
    exit 0;;
  --) shift; break;;
  *) break;;
  esac; shift
done

[[ ! -z $SYSROOT_PATH ]] || { echo "SYSROOT_PATH not set" >/dev/stderr; exit 1; }
[[ -e $SYSROOT_PATH ]] || { echo "SYSROOT_PATH not exist ($SYSROOT_PATH)" >/dev/stderr; exit 1; }

if [[ ! -e $bdir ]]; then
  cmake -B $bdir \
    -DCMAKE_BUILD_TYPE=$buildType \
    -DSYSROOT_PATH=$SYSROOT_PATH \
    $params \
    "$@"
fi
cmake --build $bdir || exit $?
if $do_install; then
  cmake --install $bdir || exit $?
fi

