#!/bin/bash

set -e 

cd build
BUILD=$(pwd)
git clone https://github.com/kobolabs/liblzma.git

cd liblzma

./configure --disable-shared --prefix=$BUILD/lzma.target
make
make install


