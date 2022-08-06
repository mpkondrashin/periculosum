#!/bin/bash

set -e 

cd build
BUILD=$(pwd)
git clone https://github.com/madler/zlib.git
cd zlib

./configure --prefix=$BUILD/zlib.target --static
make
make install


