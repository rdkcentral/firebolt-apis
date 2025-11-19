#!/usr/bin/env bash

set -e

bdir="build"
run=true
buildType="Debug"

while [[ ! -z $1 ]]; do
  case $1 in
  --clean) rm -rf $bdir;;
  --just-run)
    export LD_LIBRARY_PATH=$bdir/src:$SYSROOT_PATH/usr/lib:$LD_LIBRARY_PATH
    $bdir/FireboltCoreDemo
    exit;;
  --no-run) run=false;;
  --release) buildTarget="Release";;
  --sysroot) SYSROOT_PATH="$2"; shift;;
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
    "$@"
fi
cmake --build $bdir

if $run; then
  export LD_LIBRARY_PATH=$bdir/src:$SYSROOT_PATH/usr/lib:$LD_LIBRARY_PATH
  $bdir/FireboltCoreDemo
fi

