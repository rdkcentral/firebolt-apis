#!/usr/bin/env bash

set -e

bdir="build"
run=true

while [[ ! -z $1 ]]; do
  case $1 in
  --clean) rm -rf $bdir;;
  --no-run) run=false;;
  --just-run)
    export LD_LIBRARY_PATH=$SYSROOT_PATH/usr/lib:$LD_LIBRARY_PATH
    $bdir/FireboltCoreSDKDemo
    exit;;
  --) shift; break;;
  *) SYSROOT_PATH="$1"; shift;;
  esac; shift
done

SYSROOT_PATH=${1:-$SYSROOT_PATH}
[[ ! -z $SYSROOT_PATH ]] || { echo "SYSROOT_PATH not set" >/dev/stderr; exit 1; }
[[ -e $SYSROOT_PATH ]] || { echo "SYSROOT_PATH not exist ($SYSROOT_PATH)" >/dev/stderr; exit 1; }

[[ -e $bdir ]] || cmake -B $bdir -DSYSROOT_PATH=$SYSROOT_PATH
cmake --build $bdir

if $run; then
  export LD_LIBRARY_PATH=$SYSROOT_PATH/usr/lib:$LD_LIBRARY_PATH
  $bdir/FireboltCoreSDKDemo
fi

