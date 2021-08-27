#!/bin/bash

mkdir -p /tmp/firebolt-docs/build
mkdir -p /tmp/firebolt-docs/wiki
mkdir -p /tmp/firebolt-docs/ottxdocs

cp -r ./build/docs/markdown /tmp/firebolt-docs/build

BRANCH="$(git branch --show-current)"
# grab repo and reformat to git@github.comcast.com:<team>/<project>.wiki.git
REPO="$(git config --get remote.origin.url | sed 's/https:\/\//git\@/' | sed 's/github.comcast.com\//github.comcast.com\:/' | sed 's/.git$/.wiki.git/')"

if [ $BRANCH = 'main' -o $BRANCH = 'master' ]
then
    echo "Publishing docs to GitHub wiki..."
    echo " $REPO "

    cd /tmp/firebolt-docs/wiki/
    git clone $REPO .
    ls
    rm -r *
    cp -r ../build/markdown/* ./
    mv ./index.md ./Home.md
    git add --all
   git commit -m 'Publishing docs to wiki'
   git push
else
    echo "Publishing $BRANCH docs to ottx-docs wiki..."
    echo "ERROR: not supported yet..."
fi

yes | rm -r /tmp/firebolt-docs