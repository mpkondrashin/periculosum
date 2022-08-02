#include <sys/mman.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <cstddef>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if ( fd == -1 ) {
        return errno;
    }
    size_t len = 10;
    void *p = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) {
        printf("failed\n" );
        return 10;
    }
    printf("addr: %p\n", p);
    char *c = (char*)p;
    for (int i = 0; i < 20; i++) {
        printf("%c", c[i]);
    }
    printf("\n");
}