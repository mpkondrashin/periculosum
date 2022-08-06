#!/bin/bash

set -e 

cd build
BUILD=$(pwd)
#curl -O https://zlib.net/zlib-1.2.12.tar.gz
#git clone https://github.com/madler/zlib.git
cd zlib

./configure --prefix=$BUILD/zlib.target --static
make
make install


