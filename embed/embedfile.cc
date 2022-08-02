#include "embed.h"
#include <strings.h>
#include <errno.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    int rc = embed(argv[1], argv[2]);
    //int rc = embed("t/fa", "t/fb");
    if (rc) {
        printf("Error: %s\n", strerror(errno));
    }
    return rc;
}