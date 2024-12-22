/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 periculosum - check of file
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "process.h"
#include "magicclass.h"

const char *DEFAULT_MAGIC_DATABASE =  "magic.mgc";
const char *magic_database = DEFAULT_MAGIC_DATABASE;

const char *filename = NULL;
const char *trueFilename = NULL;

void usage() {
    fprintf(stderr, "Usage: supported [-m filename] [-l] [-h] filename\n");
    exit(2);
}

void parse_args(int argc, char **argv) {
    int option;
    while( (option = getopt(argc, argv, "m:lh")) != -1 ) {
        switch( option ) {
            case 'm':
                if (magic_database != DEFAULT_MAGIC_DATABASE) {
                    fprintf(stderr, "Only one magic databse file is supported\n");
                    usage();
                }
                magic_database = optarg;
                break;
            case 'l':
                logging = 1;
                break;
            case 'h':
                fprintf(stderr, "Determine potential threat of the file.\n"
                "Available options:\n"
                "-m filename\tprovide alternative magic file\n"
                "-l\t\tlog operations to stderr\n"
                "Exit codes:\n"
                "0 - file can not be a threat\n"
                "1 - file can be a threat and should be checked to some other tool\n"
                "2 - wrong options\n"
                "100 - error occured\n"
                );
                exit(0);
                break;
        }
    }
    if (optind < argc-2 || optind >= argc) {
        usage();
    }
    filename = argv[optind];
    trueFilename = filename;
    if (optind == argc-2) {
        trueFilename = argv[optind+1];        
    }
}

int main(int argc, char **argv)
{
    parse_args(argc, argv);
    Magic *magicMime = new Magic(MAGIC_MIME_TYPE);
    Magic *magicType = new Magic();
    int rc = is_supported(filename, trueFilename, magicMime, magicType);
    if (rc == ERROR_OCCURED) {
        fprintf(stderr, "%s\n", last_error());
    }
    return rc;
}
