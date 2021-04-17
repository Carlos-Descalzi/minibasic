#include "common.h"
#include <string.h>

static char program_memory[PROGRAM_MEMORY_LENGHT];
static char immediate_memory[IMMEDIATE_MEMORY_LENGHT];

ProgramLine* PROGRAM_MEMORY = (ProgramLine*)program_memory;
Variable VARIABLE_MEMORY[VARIABLE_TABLE_LENGHT];
char STRING_MEMORY[STRING_TABLE_LENGHT];
Value* IMMEDIATE_MEMORY = (Value*)immediate_memory;

void clear_memory(){
    memset(program_memory,0,PROGRAM_MEMORY_LENGHT);
    memset(VARIABLE_MEMORY,0,sizeof(VARIABLE_MEMORY));
    memset(immediate_memory,0,IMMEDIATE_MEMORY_LENGHT);
    memset(STRING_MEMORY,0,STRING_TABLE_LENGHT);
}
