# Periculosum
Determine potential dangerous files
by Mikhail Kondrashin

[![License](https://img.shields.io/badge/License-Apache%202-blue.svg)](https://opensource.org/licenses/Apache-2.0)

This utility by no means detects whenever particular file is dangerous or not, but provides ability to prefilter files before more sofisticated inspection like sandbox analysis or multiscanners.

It heavely dependent on [libmagic](http://www.darwinsys.com/file/) library.

## Build

```code
git clone https://github.com/mpkondrashin/periculosum.git
make
```

This will generate periculosum and magic.mgc files.

## Usage
```code
periculosum filename
```


