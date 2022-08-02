#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cstring>

#include "process.h"
#include "magicclass.h"

const char *DEFAULT_MAGIC_DATABASE =  "magic.mgc";
const char *magic_database = DEFAULT_MAGIC_DATABASE;

#ifndef PATH_MAX
#define PATH_MAX        4096 
#endif

void usage() {
    fprintf(stderr, "Usage: checker [-m filename] [-l] [-h]\n");
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
                "2 - wrong options\n"
                "100 - error occured\n"
                );
                exit(0);
                break;
        }
    }
    if (optind != argc) {
        usage();
    }
}

int main(int argc, char **argv)
{
    parse_args(argc, argv);
    try {
        Magic *magicMime = new Magic(magic_database, MAGIC_MIME_TYPE);
        Magic *magicType = new Magic(magic_database);
        for(;;) {
            char filename[PATH_MAX];
            if (!fgets(filename,  PATH_MAX, stdin) ) {
                return 100;
            }
            filename[strcspn(filename, "\r\n")] = '\0'; 
            int rc = is_supported(filename, magicMime, magicType);
            printf("%d\n", rc);
            fflush(stdout);
        }
    } catch (std::exception &e) {
        fprintf(stderr, "%s\n", e.what());
        return 100;
    }

}
