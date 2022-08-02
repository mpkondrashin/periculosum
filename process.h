#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "magicclass.h"

int is_supported(const char *filename, Magic *magicMime, Magic *magicType);
const char *last_error();
extern int logging;

#define ERROR_OCCURED 100

#endif