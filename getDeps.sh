#!/usr/bin/env bash

set -e

LIBOSMIUM_URL="https://github.com/osmcode/libosmium/archive/v2.5.4.tar.gz"
LIBOSMIUM_DIR="libosmium"

mkdir -p third_party/${LIBOSMIUM_DIR}
pushd third_party
wget --quiet -O - ${LIBOSMIUM_URL} | tar --strip-components=1 -xz -C ${LIBOSMIUM_DIR}
popd
