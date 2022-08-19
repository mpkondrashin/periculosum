# Periculosum
Determine whenever file is supported by Trend Micro Sandbox solution 

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This utility by no means detects whenever particular file is dangerous or not, but provides ability to prefilter files before more sofisticated inspection like sandbox analysis or multiscanners.

Program is based on list of supported file formats by [Trend Micro Deep Discovery Analyzer](https://success.trendmicro.com/dcx/s/solution/1122240-supported-sandbox-and-u-sandbox-file-types?language=en_US).

## Build

Build makefile and scripts are adopted for macOS, Linux, and Windows:
**Note:** To build Periculosum for Windows [Cygwin](https://www.cygwin.com/) should be installed with following packages: base, make, autoreconf, libtool, autoconf, automake, gcc-g++, zip, xxd.

```code
git clone https://github.com/mpkondrashin/periculosum.git
cd periculosum
make
```

This will generate **periculosum**, **checker** programs.

To run tests:
```code
make test
```

## Periculosum Usage
```code
periculosum filename
```

Exit code will indicate result of check:

- 0 — file is harmless
- 1 — file of this type can be malicious
- 2 — command line error
- 100 — other errors

Command line options:
- **-h** - show help and exit
- **-l** — log to stderr check operations
- **-m filename** — provide alternate magic.mgc file (default is the one in same directory as periculosum executable)

## Checker Usage
```code
./checker
```

Input file path from command line and cheker will output 1 or 0 indication whenever this file
should or should not be submitted for testing to Sandbox.

Command line options:
- **-h** - show help and exit
- **-l** — log to stderr check operations
- **-m filename** — provide alternate magic.mgc file (default is the one in same directory as periculosum executable)

**goperic** folder contains "glue" code to use checker in Go projects.