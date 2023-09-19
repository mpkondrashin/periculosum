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

FILE=build/magic.target/bin/file
[ -f ${FILE} ] || exec echo "${FILE} is missing"

MAGIC_MGC=build/magic.target/share/misc/magic.mgc
[ -f ${MAGIC_MGC} ] || exec echo "${MAGIC_MGC} is missing"

echo "Check malicious"
for f in testdata/malicious/*
do
    OUTPUT=$(./periculosum -l ${f})
    if [ "$?" != "1" ]
    then
        echo ${OUTPUT}
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
    OUTPUT=$(./periculosum -l ${f})
    if [ "$?" != "0" ]
    then
        echo ${OUTPUT}
        echo =====
        echo ${f}
        ${FILE} -m ${MAGIC_MGC} --brief ${f}
        ${FILE} -m ${MAGIC_MGC} --mime-type --brief  ${f}
        exit 1
    fi
done
echo "Done"
