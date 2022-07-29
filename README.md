# Periculosum
Determine potential dangerous files
by Mikhail Kondrashin

[![License](https://img.shields.io/badge/License-Apache%202-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This utility by no means detects whenever particular file is dangerous or not, but provides ability to prefilter files before more sofisticated inspection like sandbox analysis or multiscanners.

Its heavely dependent on [libmagic](http://www.darwinsys.com/file/) library.

## Build

Build makefile and scripts are adopted fo macOS and Linux:

```code
git clone https://github.com/mpkondrashin/periculosum.git
cd periculosum
make
```

This will generate **periculosum** and **magic.mgc** files.

## Usage
```code
periculosum filename
```

Exit code will indicate result of check:

- 0 — file is harmless
- 1 - file of this type can be malicious
- 2 - command line error
- 100 - other errors
