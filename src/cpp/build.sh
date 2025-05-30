#!/usr/bin/env bash

set -e

SYSROOT_PATH=${1:-$SYSROOT_PATH}
[[ ! -z $SYSROOT_PATH ]] || { echo "SYSROOT_PATH not set" >/dev/stderr; exit 1; }
[[ -e $SYSROOT_PATH ]] || { echo "SYSROOT_PATH not exist ($SYSROOT_PATH)" >/dev/stderr; exit 1; }

bdir="build"
idir="install"
rm -rf $bdir $idir
cmake -B $bdir -DSYSROOT_PATH=$SYSROOT_PATH
cmake --build $bdir
cmake --install $bdir

