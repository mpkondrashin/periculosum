CC=llvm-g++
SHELL = bash

#MGC=magic/animation magic/cafebabe magic/flash magic/msdos magic/pdf magic/sylk magic/archive magic/filesystems magic/mach magic/os2 magic/sgml
MGC=animation   cafebabe    elf         mach        msdos       pdf         sylk \
	archive     commands    filesystems macintosh   msooxml     rtf         uuencode \
	audio       compress    flash       mail.news   os2         sgml        windows

.PHONY: clean test

all: periculosum checker

#magic.mgc

periculosum: periculosum.cc process.o mgc.o
	${CC} $^ -L build/target/lib -l magic -o $@

checker: checker.cc process.o mgc.o
	${CC} $^ -L build/target/lib -l magic -o $@

process.o: process.cc process.h build/target/include/magic.h
	${CC} -c process.cc

mgc.o: mgc.cc
	${CC} -c mgc.cc	

mgc.cc: magic.mgc
	xxd -i magic.mgc > mgc.cc

magic.mgc: build/target/bin/file
	mkdir -p magic
	for f in $(MGC); do \
		cp build/file/magic/Magdir/$$f magic; \
	done
	build/target/bin/file -C -m magic

build/target/bin/file build/target/include/magic.h:
	./make_file.sh

test: periculosum $(wildcard magic/*)
	./check.sh

clean:
	rm -rf build
	rm periculosum
	rm magic.mgc
