#include "embed.h"
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    size_t size;
    char *c = (char*) map(argv[1], &size);
    if (c == NULL) {
        printf("map failed: %s\n", strerror(errno));
        return 1;
    }
    for(int i = 0; i < size; i++) {
        printf("%c", c[i]);
    }
    printf("\n");
}