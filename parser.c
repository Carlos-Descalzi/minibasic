#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "common.h"
#include "program.h"
#include "keywords.h"
#include <string.h>
#include "eval.h"
#include "stack.h"
#include "variables.h"

static Token token;

static int parse_program_line(char* input_buffer, unsigned short number);
static int parse_statement(char* input_buffer);
//static int parse_call(char *input_buffer);
static int parse_term(char *input_buffer);
static int parse_factor(char* input_buffer);

int parse_program(char* input_buffer){
    scan_init();

    if (scan(input_buffer, &token) != SCAN_OK){
        return PARSER_SYNTAX_ERROR;
    }

    if (token.type == TOKEN_NUMBER){
        return parse_program_line(input_buffer, (unsigned short)token.ivalue);
    } 
    return parse_statements(input_buffer);
}

int parse_statements(char* input_buffer){
    // TODO Multiple statements 
    return parse_statement(input_buffer);
}

static int parse_program_line(char* input_buffer, unsigned short number){
    program_add_line(number, input_buffer+scanner_pos());
    return PARSER_OK;
}

static int parse_statement(char* input_buffer){
    switch (token.type){
        case TOKEN_PRINT:
            return do_print(input_buffer);
        case TOKEN_LIST:
            return do_list(input_buffer);
        case TOKEN_RUN:
            return do_run(input_buffer);
        case TOKEN_LET:
            return do_let(input_buffer);
        case TOKEN_GOTO:
            return do_goto(input_buffer);
        case TOKEN_FOR:
            return do_for(input_buffer);
        case TOKEN_NEXT:
            return do_next(input_buffer);
        case TOKEN_GOSUB:
            return do_gosub(input_buffer);
        case TOKEN_RETURN:
            return do_return(input_buffer);
    }

    return PARSER_SYNTAX_ERROR;//PARSER_OK;
}

int parse_expr(char *input_buffer){
    int r;
    Value left;
    Value right;
    Value result;

    if ((r = parse_term(input_buffer)) != PARSER_OK){
        return r;
    }

    r =scan(input_buffer, &token);

    if (r != SCAN_EOF){
        if (r!= SCAN_OK){
            return PARSER_SYNTAX_ERROR;
        }
        if (token.type == TOKEN_PLUS){
            if ((r = parse_term(input_buffer)) == PARSER_OK){
                stack_pop(&right);
                stack_pop(&left);
                if (!eval_sum(&left, &right, &result)){
                    return PARSER_EVAL_ERROR;
                }
                stack_push(&result);
            }
            return r;
        } else if (token.type == TOKEN_MINUS){
            if ((r = parse_term(input_buffer)) == PARSER_OK){
                stack_pop(&right);
                stack_pop(&left);
                if (!eval_sub(&left, &right, &result)){
                    return PARSER_EVAL_ERROR;
                }
                stack_push(&result);
            }
            return r;
        } 
        rollback_scan();
    }

    return PARSER_OK;
    
}
static int parse_term(char *input_buffer){
    int r;
    Value left;
    Value right;
    Value result;

    if ((r = parse_factor(input_buffer)) != PARSER_OK){
        return r;
    }

    if ((r = scan(input_buffer, &token)) != SCAN_EOF){
        if (r!= SCAN_OK){
            return PARSER_SYNTAX_ERROR;
        }
        if (token.type == TOKEN_MULT){
            if ((r = parse_factor(input_buffer)) == PARSER_OK){
                stack_pop(&right);
                stack_pop(&left);
                if (!eval_mul(&left, &right, &result)){
                    return PARSER_EVAL_ERROR;
                }
                stack_push(&result);
            } 
            return r;
        } else if (token.type == TOKEN_DIV){
            if ((r = parse_factor(input_buffer)) == PARSER_OK){
                stack_pop(&right);
                stack_pop(&left);
                if (!eval_div(&left, &right, &result)){
                    return PARSER_EVAL_ERROR;
                }
                stack_push(&result);
            }
            return r;
        } 
        rollback_scan();
    }

    return PARSER_OK;
}

static int parse_factor(char* input_buffer){
    int r;
    Value value;

    if ((r = scan(input_buffer, &token)) == SCAN_OK){
        switch(token.type){
            case TOKEN_ID:
                variables_get(token.svalue,&value);
                stack_push(&value);
                break;
            case TOKEN_NUMBER:
                stack_push_int(token.ivalue);
                break;
            case TOKEN_STRING:
                stack_push_str(token.svalue);
                break;
            case TOKEN_LPAR:
                if ((r = parse_expr(input_buffer)) != PARSER_OK){
                    return r;
                }
                if (
                    (r = scan(input_buffer, &token)) != SCAN_OK 
                    || (token.type != TOKEN_RPAR)
                ){
                    return PARSER_SYNTAX_ERROR;
                }
                break;
        }
        return PARSER_OK;
    }
    return PARSER_SYNTAX_ERROR;
}

