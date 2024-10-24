
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
# Makefile - build periculosum and checker programs
# Available options: all, test, clean
#

ifdef OS
    LIBS=build/magic.target/lib/libmagic.a
#	FIX_ASLR=cat fix_aslr.ps1 | powershell.exe -Command -
else
	LIBS=build/magic.target/lib/libmagic.a \
		build/lzma.target/lib/liblzma.a \
		build/bzip2.target/lib/libbz2_static.a \
		build/zlib.target/lib/libz.a
endif

CC=g++ -std=c++11

ifeq ($(shell uname),Darwin)
    CFLAGS=-mmacosx-version-min=14.5
else
    CFLAGS=
endif

SHELL = bash

MGC=animation   cafebabe    elf         mach        msdos       pdf         sylk \
	archive     commands    filesystems macintosh   msooxml     rtf         uuencode \
	audio       compress    flash       mail.news   os2         sgml        windows

.PHONY: clean test shell

all: periculosum checker

periculosum: periculosum.cc process.o mgc.o magicclass.o ${LIBS}
	${CC} ${CFLAGS} $^ -o $@

checker: checker.cc process.o mgc.o magicclass.o ${LIBS}
	${CC} ${CFLAGS} $^ -o $@ 

process.o: process.cc process.h build/magic.target/include/magic.h
	${CC} -c process.cc

mgc.o: mgc.cc
	${CC} -c mgc.cc	

magicclass.o: magicclass.cc magicclass.h
	${CC} -c magicclass.cc	

mgc.cc: magic.mgc
#	${FIX_ASLR}
#ifdef OS
#	echo "xdd"
#	which xdd
#	echo $(shell which xdd)
#	echo $(shell which xdd.exe)
#	XDD_DIR=$(dirname $(which xdd))
#	echo "Get-Item -Path ${XDD_DIR}/*.exe | %{ Set-ProcessMitigation -Name $$_.Name -Disable ForceRelocateImages }" | powershell.exe -Command -
#endif
	xxd -i magic.mgc mgc.cc

magic.mgc: build/magic.target/bin/file
	mkdir -p magic
	for f in $(MGC); do \
		cp build/file/magic/Magdir/$$f magic; \
	done
	build/magic.target/bin/file -C -m magic

test: periculosum $(wildcard magic/*)
	${SHELL} check.sh

build/zlib.target/lib/libz.a:
	${SHELL} make_zlib.sh

build/bzip2.target/lib/libbz2_static.a:
	${SHELL} make_bzip2.sh

build/lzma.target/lib/liblzma.a:
	${SHELL} make_lzma.sh

build/magic.target/include/magic.h build/magic.target/lib/libmagic.a:
	${SHELL} make_magic.sh

shell:
	echo ${SHELL}

clean:
	rm -rf build magic
	rm -f periculosum checker magic.mgc mgc.cc
	rm -f *.o
