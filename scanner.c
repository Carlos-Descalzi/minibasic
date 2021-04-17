#include <ctype.h>
#include <string.h>

#include "scanner.h"

int ptr;
int prev_ptr;

/**
 * Moves forward until the next valid character or \0
 **/
static char forward(char* buff);
/**
 * Next character in the buffer
 **/
static char next_char(char* buff);
/**
 * Is operation ?
 **/
static int isop(char c);
/**
 * Is EOF? \0 or \n
 **/
static int iseof(char c);
/**
 * Initializes a token
 **/

static char sbuff[100];
static int sptr = 0;

int scanner_pos(void){
    return ptr;
}

int scan(char* buff, Token* token){
    memset(sbuff,0,100);
    sptr = 0;

    token_init(token);

    prev_ptr = ptr;

    char c = forward(buff);

    if (iseof(c)){
        return SCAN_EOF;
    }
    if (isalpha(c)){

        while (c && isalpha(c)){
            sbuff[sptr++] = c;
            c = next_char(buff);
        }
        sbuff[sptr] = 0;

        if (!strcmp(sbuff,"to")){
            token->type = TOKEN_TO;
        } else if (!strcmp(sbuff,"if")){
            token->type = TOKEN_IF;
        } else if (!strcmp(sbuff,"then")){
            token->type = TOKEN_THEN;
        } else if (!strcmp(sbuff,"else")){
            token->type = TOKEN_ELSE;
        } else {
            token->type = TOKEN_ID;
            token->svalue = sbuff;
            //printf("%s\n",token->svalue);
            // TODO
        }
        return SCAN_OK;
    } else if (isdigit(c)){
        while (c && isdigit(c)){
            sbuff[sptr++] = c;
            c = next_char(buff);
        }
        ptr--;
        sbuff[sptr] = 0;
        token->type = TOKEN_NUMBER;
        token->ivalue = atoi(sbuff);
        return SCAN_OK;
    } else if (c == '='){
        token->type = TOKEN_EQ;
        return SCAN_OK;
    } else if (c == '('){
        token->type = TOKEN_LPAR;
        return SCAN_OK;
    } else if (c == ')'){
        token->type = TOKEN_RPAR;
        return SCAN_OK;
    } else if (c == '+'){
        token->type = TOKEN_PLUS;
        return SCAN_OK;
    } else if (c == '-'){
        token->type = TOKEN_MINUS;
        return SCAN_OK;
    } else if (c == '*'){
        token->type = TOKEN_MULT;
        return SCAN_OK;
    } else if (c == '/'){
        token->type = TOKEN_DIV;
        return SCAN_OK;
    } else if (isop(c)){
        token->type = TOKEN_OP;
        token->cvalue = c;
        return SCAN_OK;
    } else if (c == '"'){
        token->svalue = sbuff;
        c = next_char(buff);
        while(c && c!= '"'){
            sbuff[sptr++] = c;
            c = next_char(buff);
        }
        sbuff[sptr] = '\0';
        token->type = TOKEN_STRING;
        return SCAN_OK;
    }
    //printf("Unknown %d '%c'\n",c,c);

    return SCAN_ERROR;
}

void token_init(Token* token){
    memset(token,0,sizeof(Token));
}

char next_char(char* buff){
    return buff[ptr++];
}
    
char forward(char* buff){
    char c;
    while((c = buff[ptr]) && isblank(c)){
        ptr++;
    }
    return buff[ptr++];
}

void scan_init(){
    ptr = 0;
}

void rollback_scan(){
    ptr = prev_ptr;
}

int isop(char c){
    switch(c){
        case '<':
        case '>':
        case '^':
        case ':':
        case ',':
            return 1;
    }
    return 0;
}

int iseof(char c){
    return !c || c == '\n';
}
