#include <stdio.h>
#include "keywords.h"
#include "parser.h"
#include "scanner.h"
#include "common.h"
#include "program.h"
#include "stack.h"
#include "variables.h"
#include "console.h"

static ProgramLine* next_line;

static int do_print(char* input_buffer);
static int do_list(char* input_buffer);
static int do_run(char* input_buffer);
static int do_pin(char* input_buffer);
static int do_sleep(char* input_buffer);
static int do_let(char* input_buffer);
static int do_goto(char* input_buffer);
static int do_for(char* input_buffer);
static int do_next(char* input_buffer);
static int do_gosub(char* input_buffer);
static int do_return(char* input_buffer);

Keyword KEYWORDS[] = {
    { "print",  do_print    },
    { "list",   do_list     },  
    { "run",    do_run      },
    { "pin",    do_pin      },
    { "let",    do_let      },
    { "goto",   do_goto     },
    { "sleep",  do_sleep    },
    { "for",    do_for      },
    { "next",   do_next     },
    { "gosub",  do_gosub    },
    { "return", do_return   },
    { NULL,     NULL        }
};

static int do_print(char* input_buffer){
    Value value;

    if (parse_expr(input_buffer) == PARSER_OK){
        stack_pop(&value);
        if (value.type == VT_STR){
            String* string = (String*)value.svalue;
            for (int i=0;i<string->length;i++){
                console_write_chr(string->string[i]);
            }
        } else if (value.type == VT_INT){
            console_write_int(value.ivalue);
        }
    }

    console_write_chr('\n');

    return PARSER_OK;
}



static int do_list(char* input_buffer){
    program_list();
    return PARSER_OK;
}
static int do_run(char* input_buffer){
    int r;
    char* code;
    next_line = program_first();

    while (next_line->number != 0){
        code = next_line->code;
        next_line = next_line->next;
        if ((r = parse_program(code)) != PARSER_OK){
            return r;
        }
    }

    return PARSER_OK;
}
static int do_pin(char* input_buffer){
    return PARSER_OK;
}
static int do_let(char* input_buffer){
    Token token;
    Value name;
    Value value;
    int r;

    if (scan(input_buffer, &token)!=SCAN_OK || token.type != TOKEN_ID){
        return PARSER_SYNTAX_ERROR;
    }
    stack_push_str(token.svalue);
    if (scan(input_buffer, &token)!=SCAN_OK || token.type != TOKEN_EQ){
        return PARSER_SYNTAX_ERROR;
    }
    if ((r = parse_expr(input_buffer)) == PARSER_OK){
        stack_pop(&value);
        stack_pop(&name);
        variables_add(&name, &value);
    }
    return r;
}
static int do_sleep(char* input_buffer){
    return PARSER_OK;
}
static int do_goto(char* input_buffer){
    int r;
    if ((r = parse_expr(input_buffer)) == PARSER_OK){
        Value value;
        stack_pop(&value);

        if (value.type != VT_INT){
            return PARSER_EVAL_ERROR;
        }
        next_line = program_find(value.ivalue);
    }
    return r;
}
static int do_for(char* input_buffer){
    int r;
    Token token;
    Value name;
    Value start;

    if (scan(input_buffer, &token)!=SCAN_OK || token.type != TOKEN_ID){
        return PARSER_SYNTAX_ERROR;
    }
    stack_push_str(token.svalue);
    if (scan(input_buffer, &token)!=SCAN_OK || token.type != TOKEN_EQ){
        return PARSER_SYNTAX_ERROR;
    }
    if ((r = parse_expr(input_buffer)) == PARSER_OK){
        stack_pop(&start);
        stack_pop(&name);
        variables_add(&name, &start);
    }
    if (scan(input_buffer, &token)!=SCAN_OK || token.type != TOKEN_TO){
        return PARSER_SYNTAX_ERROR;
    }
    if ((r = parse_expr(input_buffer)) != PARSER_OK){
        return r;
    }
    // leave the end value in stack
    // push step
    stack_push_int(1);
    // push current line
    stack_push_int(next_line->number);
    return PARSER_OK;
}
static int do_next(char* input_buffer){
    Token token;
    Value value;
    Value line;
    Value end;
    Value step;
    if (scan(input_buffer, &token)!=SCAN_OK || token.type != TOKEN_ID){
        return PARSER_SYNTAX_ERROR;
    }
    variables_get(token.svalue, &value);

    stack_pop(&line);
    stack_pop(&step);
    stack_pop(&end);

    value.ivalue += step.ivalue;

    if ((step.ivalue > 0 && value.ivalue <= end.ivalue)
        || (step.ivalue < 0 && value.ivalue >= end.ivalue)){
        stack_push(&end);
        stack_push(&step);
        stack_push(&line);
        variables_add_int(token.svalue,value.ivalue);
        next_line = program_find(line.ivalue);
    }

    return PARSER_OK;
}
static int do_gosub(char* input_buffer){
    int r;
    if ((r = parse_expr(input_buffer)) == PARSER_OK){
        Value value;
        stack_pop(&value);

        if (value.type != VT_INT){
            return PARSER_EVAL_ERROR;
        }
        stack_push_int(next_line->number);
        next_line = program_find(value.ivalue);
    }
    return PARSER_OK;
}
static int do_return(char* input_buffer){
    Value value;
    stack_pop(&value);
    next_line = program_find(value.ivalue);
    return PARSER_OK;
}
