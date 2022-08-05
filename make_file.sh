#!/bin/bash

set -e

OS="$(uname)"
if [ "${OS}" = "Darwin" ]; then
    GOOS="darwin"
elif [ "${OS}" = "Linux" ]; then
    GOOS="linux"
else
    exec echo "Unknown OS: ${OS}"
fi

ARCH="$(uname -m)"
 
if [ "${ARCH}" = "x86_64" ]; then
    GOARCH="amd64"
elif [ "${ARCH}" = "arm64" ]; then
    GOARCH="arm64"
else
    exec echo "Unknown architecture: ${ARCH}"
fi
echo Build for "${GOOS} ${GOARCH}"


if [ "${GOOS}" = "darwin" ]; then
    which install || brew install
    which autoconf || brew autoconf
    which automake || brew automake
    which libtool || brew libtool
elif [ "${GOOS}" = "linux" ]; then
    echo "Skip install build tools for linux"
#    apt-get install \
#            automake \
#            gcc \
#            libtool \
#            make \
#            python \
#            zlib1g-dev
fi

BASE=$(pwd)
#TARGET="magic_${GOOS}_${GOARCH}"
TEMP="build"
PREFIX=${TEMP}/target
echo "PREFIX=${PREFIX}"
(
    mkdir -p ${TEMP}
    cd ${TEMP}
    git clone https://github.com/file/file.git
    cd file

    autoreconf -f -i
    ./configure --prefix=${BASE}/${PREFIX}  --enable-static --disable-silent-rules
    make -j4
    make -C tests check
    make install
)

#mkdir -p ${TARGET}
#cp ${PREFIX}/share/misc/magic.mgc ${PREFIX}/bin/file  ${TARGET}
#zip -r ${TARGET}.zip ${TARGET}
#echo "Cleanup"
#rm -rf ${TARGET}
#rm -rf ${TEMP}


