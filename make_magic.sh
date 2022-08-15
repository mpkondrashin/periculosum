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
# make_file.sh - download nad build static version on magic library.
# This script should result libmagic.a file in
# build/magic.target/lib folder
#

set -eu
export PS4='> '
set -x

BASE=$(pwd)
TEMP="build"
PREFIX=${TEMP}/magic.target

mkdir -p ${TEMP}
cd ${TEMP}

git config --global core.autocrlf input

if [ -d file/.git ]
then
    cd file
    git pull
else
    git clone https://github.com/file/file.git
    cd file
fi

autoreconf -f -i
./configure --prefix=${BASE}/${PREFIX}  --enable-static --disable-silent-rules
make -j4
make -C tests check
make install
