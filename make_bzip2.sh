#!/bin/bash

set -e 

cd build
BUILD=$(pwd)
#git clone https://github.com/libarchive/bzip2.git

mkdir -p bzip2.build
cd bzip2.build

cmake -DENABLE_STATIC_LIB=ON -DCMAKE_INSTALL_PREFIX:PATH=${BUILD}/bzip2.target ../bzip2
cmake --build . --target install --config Release
