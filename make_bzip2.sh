#!/bin/bash

#
# Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
# You may use, distribute and modify this code under the
# terms of the MIT license.
# You should have received a copy of the MIT license with
# this file. If not, please write to: mkondrashin@gmail.com
#
# Lates version of this file can be found at following URL:
# https://github.com/mpkondrashin/periculosum
#
# make_bzip2.sh - download and build static version on bzip2 library.
# This script should result libbz2_static.a file in
# build/bzip2.target/lib folder
#

set -euo pipefail
export PS4='> '
set -x

cd build
BUILD=$(pwd)

if [ -d bzip2/.git ]
then
    cd bzip2
    git pull
    cd ..
else
    git clone --depth 1 https://github.com/libarchive/bzip2.git
fi

mkdir -p bzip2.build
cd bzip2.build

cmake -DENABLE_STATIC_LIB=ON -DCMAKE_INSTALL_PREFIX:PATH=${BUILD}/bzip2.target ../bzip2
cmake --build . --target install --config Release

cd ../bzip2.target
if [ ! -d lib ]; then
	mkdir -p lib
    cp lib64/libbz2_static.a lib/libbz2_static.a
fi
