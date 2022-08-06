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
# make_zlib.sh - download nad build static version on zlib library.
# This script should result libmagic.a file in
# build/zlib.target/libz.a folder
#

set -e 

cd build
BUILD=$(pwd)


if [ -d zlib/.git ]
then
    cd zlib
    git pull
else
    git clone https://github.com/madler/zlib.git
    cd zlib
fi



./configure --prefix=$BUILD/zlib.target --static
make
make install


