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
# prepare_linux.sh - install all required to build for darwin
#

set -e

apt-get install -y \
    automake \
    gcc \
    g++ \
    libtool \
    make \
    zlib1g-dev \
    cmake
