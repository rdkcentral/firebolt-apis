#!/bin/bash

# Copyright 2021 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

mkdir -p /tmp/firebolt-docs/build
mkdir -p /tmp/firebolt-docs/wiki
mkdir -p /tmp/firebolt-docs/ottxdocs

cp -r ./build/docs/wiki /tmp/firebolt-docs/build

BRANCH="$(git branch --show-current)"
# grab repo and reformat to git@github.comcast.com:<team>/<project>.wiki.git
REPO="$(git config --get remote.origin.url | sed 's/https:\/\//git\@/' | sed 's/github\.com\//github\.com:/' | sed 's/.git$/.wiki.git/')"

if [ $BRANCH = 'main' -o $BRANCH = 'master' ]
then
    echo "Publishing docs to GitHub wiki..."
    echo " $REPO "

    cd /tmp/firebolt-docs/wiki/
    git clone $REPO .
    ls
    rm -r *
    cp -r ../build/wiki ./

    git add --all
   git commit -m 'Publishing docs to wiki'
   git push
else
    echo "Publishing $BRANCH docs to ottx-docs wiki..."
    echo "ERROR: not supported yet..."
fi

yes | rm -r /tmp/firebolt-docs