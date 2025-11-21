#!/usr/bin/env bash

set -e

package="package"
version="0.1.0-unknown"
sub_path=
dst=

while [[ ! -z $1 ]]; do
  case $1 in
  --package) package="$2"; shift;;
  --version) version="$2"; shift;;
  --subpath) sub_path="$2"; shift;;
  --dst) dst="$2"; shift;;
  esac; shift
done

version="${version#v}"
dist_name="$package-$version"
dist_path="build/$dist_name"

mkdir -p "$dist_path"
rm -f build/$package-*.tar.gz

if [[ -z $sub_path ]]; then
  git checkout-index -af --prefix="$dist_path/"
else
  git ls-files $sub_path | git checkout-index --stdin -qf --prefix="$dist_path.tmp/"
  mv -T "$dist_path.tmp/$sub_path/" "$dist_path/"
fi
sed -i -e '/# <VERSION_BLOCK>/,/# <\/VERSION_BLOCK>/cset(PROJECT_VERSION \"'"$version"'\")' "$dist_path/CMakeLists.txt"
tar -czf "build/$dist_name.tar.gz" -C "build" "$dist_name"
echo "sha256sum  : $(sha256sum build/$dist_name.tar.gz)"

if [[ ! -z "$dst" ]]; then
  mkdir -p "$dst"
  cp "build/$dist_name.tar.gz" "$dst/"
fi

