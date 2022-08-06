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
# prepare_darwin.sh - install all required to build for darwin
#

set -e

which install || brew install
which autoconf || brew autoconf
which automake || brew automake
which libtool || brew libtool
which cmake || brew cmake
