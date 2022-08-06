/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 process.h - process one file declarations
*/

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "magicclass.h"

int is_supported(const char *filename, Magic *magicMime, Magic *magicType);
const char *last_error();
extern int logging;

#define ERROR_OCCURED 100

#endif