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
# make_lzma.sh - download nad build static version on lzma library.
# This script should result liblzma.a file in
# build/lzma.target/lib folder
#

set -e 

cd build
BUILD=$(pwd)
git clone https://github.com/kobolabs/liblzma.git

cd liblzma

./configure --disable-shared --prefix=$BUILD/lzma.target
make
make install


