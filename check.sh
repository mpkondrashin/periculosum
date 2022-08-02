#!/bin/bash

FILE=build/target/bin/file
MAGIC_MGC=build/target/share/misc/magic.mgc

#${FILE} -C -m magic
#ls -lh magic.mgc

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
