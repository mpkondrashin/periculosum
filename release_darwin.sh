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
# release_darwin.sh - pack release files to one zip file
#

set -eu
export PS4='> '
set -x

cd build

rm -rf periculosum
mkdir periculosum
cp ../periculosum periculosum
cp ../checker periculosum
cp ../LICENSE periculosum
cp ../README.md periculosum

zip -r ../periculosum_darwin64.zip periculosum
