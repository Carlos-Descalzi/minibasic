#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <stdlib.h>

#define TOKEN_UNDEF     0
#define TOKEN_NUMBER    1
#define TOKEN_ID        2
#define TOKEN_OP        3
#define TOKEN_IF        4
#define TOKEN_THEN      5
#define TOKEN_ELSE      6
#define TOKEN_TO        9
#define TOKEN_NEXT      10
#define TOKEN_STRING    11

#define TOKEN_COMMA     12
#define TOKEN_LPAR      13
#define TOKEN_RPAR      14
#define TOKEN_EQ        15
#define TOKEN_PLUS      16
#define TOKEN_MINUS     17
#define TOKEN_MULT      18
#define TOKEN_DIV       19

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
