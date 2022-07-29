#ifndef __PROCESS_H__
#define __PROCESS_H__

int is_supported(const char * database, const char *filename);
const char *last_error();
extern int logging;

#define ERROR_OCCURED 100

#endif