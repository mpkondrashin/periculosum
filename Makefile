#CC=llvm-g++ -std=c++11
CC=g++ -std=c++11
SHELL = bash

#MGC=magic/animation magic/cafebabe magic/flash magic/msdos magic/pdf magic/sylk magic/archive magic/filesystems magic/mach magic/os2 magic/sgml
MGC=animation   cafebabe    elf         mach        msdos       pdf         sylk \
	archive     commands    filesystems macintosh   msooxml     rtf         uuencode \
	audio       compress    flash       mail.news   os2         sgml        windows

.PHONY: clean test

all: periculosum checker

#magic.mgc

LIBS=build/target/lib/libmagic.a \
	build/bzip2.target/lib/libbz2_static.a \
	build/lzma.target/lib/liblzma.a \
	build/zlib.target/lib/libz.a

periculosum: periculosum.cc process.o mgc.o magicclass.o ${LIBS}
	${CC} $^ -o $@

checker: checker.cc process.o mgc.o magicclass.o ${LIBS}
	${CC} $^ -o $@

process.o: process.cc process.h build/target/include/magic.h
	${CC} -c process.cc

mgc.o: mgc.cc
	${CC} -c mgc.cc	

magicclass.o: magicclass.cc magicclass.h
	${CC} -c magicclass.cc	

mgc.cc: magic.mgc
	xxd -i magic.mgc > mgc.cc

magic.mgc: build/target/bin/file
	mkdir -p magic
	for f in $(MGC); do \
		cp build/file/magic/Magdir/$$f magic; \
	done
	build/target/bin/file -C -m magic

test: periculosum $(wildcard magic/*)
	./check.sh

build/zlib.target/lib/libz.a:
	./make_zlib.sh

build/bzip2.target/lib/libbz2_static.a:
	./make_bzip2.sh

build/lzma.target/lib/liblzma.a:
	./make_lzma.sh

build/target/lib/libmagic.a:
	./make_file.sh

clean:
	rm -rf build
	rm periculosum
	rm magic.mgc
