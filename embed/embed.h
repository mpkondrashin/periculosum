#ifndef __EMBED_H__
#define __EMBED_H__

#include <stddef.h>

int embed(const char *filename, const char *data);
int extract(const char *filename);
void * map(const char *filename, size_t *psize);

#endif