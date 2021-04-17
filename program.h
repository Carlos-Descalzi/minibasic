#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "common.h"
#define         program_first()     PROGRAM_MEMORY

void            program_add_line   (int number, char* program_line);
void            program_list       (void);
ProgramLine*    program_find       (int number);


#endif
