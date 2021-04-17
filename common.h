#ifndef _COMMON_H_
#define _COMMON_H_

#include "common.h"

#define STRING_TABLE_LENGHT     1024
#define VARIABLE_TABLE_LENGHT   1024
#define PROGRAM_MEMORY_LENGHT   8192
#define IMMEDIATE_MEMORY_LENGHT 256

enum ValueType {
    VT_INT = 0,
    VT_STR
};

typedef struct String {
    unsigned char length;
    char string[1];
} String;

typedef struct Value {
    enum ValueType type;
    union {
        int ivalue;
        String* svalue;
    };
} Value;

typedef struct Variable {
    String* name;
    Value value;
} Variable;

typedef struct ProgramLine {
    struct ProgramLine* next;
    unsigned short number;
    char code[1];
} ProgramLine;

extern ProgramLine* PROGRAM_MEMORY;
extern Value* IMMEDIATE_MEMORY;
extern Variable VARIABLE_MEMORY[];
extern char STRING_MEMORY[];

void clear_memory();

#endif
