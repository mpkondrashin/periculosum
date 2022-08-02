
//#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>


const int SIGNATURE_SIZE = 8;
char SIGNATURE[SIGNATURE_SIZE] = {'M', 'a', 'G', 'i', 'C', '1', '0', '0'};


struct Suffix {
    char signature_a[SIGNATURE_SIZE];
    size_t offset;
    char signature_b[SIGNATURE_SIZE];
};

void init_suffix(Suffix *s, size_t offset) {
      for(int i = 0; i < SIGNATURE_SIZE; i++) {
        s->signature_a[i] = SIGNATURE[i];
        s->signature_b[i] = SIGNATURE[i];
    }
    s->offset = offset;
}

int check_suffix(Suffix *s) {
     for(int i = 0; i < SIGNATURE_SIZE; i++)
        if (s->signature_a[i] != SIGNATURE[i] || s->signature_b[i] != SIGNATURE[i])
            return 1;
    return 0;
}

int check_suffix_in_file(FILE *f) {
    if (fseek(f, -sizeof(Suffix), SEEK_END)) return 2;
    Suffix s;
    size_t size = fread(&s, sizeof(Suffix), 1, f);
    if (size != 1) return 3;
    if (!check_suffix(&s) ) return 4;
    return 0;
}

size_t file_length(FILE *f) {
    if( fseek(f, 0L, SEEK_END) ) return -1L;
    long size = ftell(f);
    if( size == -1L) return -1L;
    if( fseek(f, 0L, SEEK_SET) ) return -1L;
    return size;
}

int embed(const char *filename, const char *data) {
    FILE *f = fopen(filename, "a+");
    if ( !f ) {
        return 1;
    }
    int check = check_suffix_in_file(f);
    if ( check ) return check;
    FILE *d = fopen(data, "r");
    if (!d) return 5;
    size_t data_size = file_length(d);
    if ( data_size == -1L ) return 6;
    Suffix s;
    init_suffix(&s, data_size + sizeof(Suffix));
    for(;;) {
        char c = fgetc(d);
        if( feof(d) ) {
            break;
        }
        fputc(c, f);
    }
    size_t n = fwrite(&s, sizeof(Suffix), 1, f);
    fclose(d);
    fclose(f);
    if (n != 1) return 7;
    return 0;   
}


int extract(const char *filename) {
    FILE *f = fopen(filename, "r");
    if ( !f ) return 1;
    if (fseek(f, -sizeof(Suffix), SEEK_END)) return 1;
    size_t end = ftell(f);
    Suffix s;
    size_t size = fread(&s, sizeof(Suffix), 1, f);
    if (size != 1) return 2;
    for(int i = 0; i < SIGNATURE_SIZE; i++)
        if (s.signature_a[i] != SIGNATURE[i] || s.signature_b[i] != SIGNATURE[i])
            return 3;
    if (fseek(f, -s.offset, SEEK_END) ) return 4;
    size_t start = ftell(f);
    for(size_t i = start; i < end; i++) {
        char c = fgetc(f);
        if( feof(f) ) return 5;
        printf("%c", c);
    }
    fclose(f);
    return 0;   
}

//         start       end
// --------|---------|==|
//         <--s.offset-->

void * map(const char *filename, size_t *psize) {
    FILE *f = fopen(filename, "r");
    if ( !f ) return NULL;
    if (fseek(f, -sizeof(Suffix), SEEK_END)) return NULL;
    size_t end = ftell(f);
    Suffix s;
    size_t size = fread(&s, sizeof(Suffix), 1, f);
    if (size != 1) return NULL;
    for(int i = 0; i < SIGNATURE_SIZE; i++)
        if (s.signature_a[i] != SIGNATURE[i] || s.signature_b[i] != SIGNATURE[i])
            return NULL;
    if (fseek(f, -s.offset, SEEK_END) ) return NULL;
    size_t start = ftell(f);
    int fd = fileno(f);
    if (psize) {
        *psize = end-start;
    }
    //if (fseek(f, start, SEEK_SET)) return NULL;
    //printf("start: %ld\n", start);
    //printf("end: %ld\n", end);
    //printf(mmap(NULL, end-start, PROT_READ, MAP_PRIVATE, fd, start);
    long page_size = sysconf(_SC_PAGE_SIZE);
    int round_offset = start/page_size*page_size;
    char *p = (char*)mmap(NULL, end-start, PROT_READ, MAP_PRIVATE, fd, round_offset);
    if (p == MAP_FAILED) return NULL;
    p += start-round_offset;
    return p;   
}