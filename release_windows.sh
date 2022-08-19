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
# release_windows.sh - pack release files to one zip file
#

set -eu
export PS4='> '
set -x

cd build

rm -rf periculosum
mkdir periculosum
cp ../periculosum.exe periculosum
cp ../checker.exe periculosum
cp ../LICENSE periculosum
cp ../README.md periculosum
cp $(which cygstdc++-6.dll) periculosum
cp $(which cygwin1.dll) periculosum
cp $(which cyggcc_s-seh-1.dll) periculosum

zip -r ../periculosum_windows64.zip periculosum

