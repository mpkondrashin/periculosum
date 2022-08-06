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

set -e 

cd build
BUILD=$(pwd)
git clone https://github.com/libarchive/bzip2.git

mkdir -p bzip2.build
cd bzip2.build

cmake -DENABLE_STATIC_LIB=ON -DCMAKE_INSTALL_PREFIX:PATH=${BUILD}/bzip2.target ../bzip2
cmake --build . --target install --config Release
