#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <stdlib.h>

#define TOKEN_UNDEF     0
#define TOKEN_NUMBER    1
#define TOKEN_ID        2
#define TOKEN_OP        3
#define TOKEN_STRING    4
#define TOKEN_COMMA     5
#define TOKEN_LPAR      6
#define TOKEN_RPAR      7
#define TOKEN_EQ        8
#define TOKEN_PLUS      9
#define TOKEN_MINUS     10
#define TOKEN_MULT      11
#define TOKEN_DIV       12

#define TOKEN_PRINT     20
#define TOKEN_LIST      21
#define TOKEN_RUN       22
#define TOKEN_LET       23
#define TOKEN_GOTO      24
#define TOKEN_FOR       25
#define TOKEN_TO        26
#define TOKEN_NEXT      27
#define TOKEN_GOSUB     28
#define TOKEN_RETURN    29
#define TOKEN_IF        30
#define TOKEN_THEN      31
#define TOKEN_ELSE      32

#define SCAN_OK         0
#define SCAN_EOF        -1
#define SCAN_ERROR      -2

typedef struct Symbol {
    char* name;
    unsigned char type;
    unsigned char addr;
    struct Symbol* next;
} Symbol;

typedef struct {
    unsigned char type;
    union {
        Symbol* symbol;
        int ivalue;
        char cvalue;
        char* svalue;
    };
} Token;

void    token_init      (Token* token);
/**
 * Initialize scan buffers and pointers
 **/
void    scan_init       (void);
/** 
 * Scans next token in input buffer
 **/
int     scan            (char* buff, Token* token);

void    rollback_scan   (void);

int     scanner_pos     (void);

#endif
