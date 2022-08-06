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
# check.sh - run tests
#

set -e

FILE=build/target/bin/file
MAGIC_MGC=build/magic.target/share/misc/magic.mgc

echo "Check malicious"
for f in testdata/malicious/*
do
    ./periculosum -l ${f} > output.txt
    if [ "$?" != "1" ]
    then
        cat output.txt
        echo =====
        echo ${f}
        ${FILE} -m ${MAGIC_MGC} --brief ${f}
        ${FILE} -m ${MAGIC_MGC} --mime-type --brief  ${f}
        exit 1
    fi
done

echo "Check innocent"
for f in testdata/innocent/*
do
    ./periculosum -l ${f} > output.txt
    if [ "$?" != "0" ]
    then
        cat output.txt
        echo =====
        echo ${f}
        ${FILE} -m ${MAGIC_MGC} --brief ${f}
        ${FILE} -m ${MAGIC_MGC} --mime-type --brief  ${f}
        exit 1
    fi
done
echo "Done"
