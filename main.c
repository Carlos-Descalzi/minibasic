#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"
#include "parser.h"
#include "common.h"
#include "strings.h"
#include "console.h"
#include "stack.h"

int main(int argc, char **argv){
    char linebuffer[256];
    int r;

    strings_init();
    clear_memory();

    console_write_str(" **** MiniBASIC V1.0 **** \n\n");

    while(1){
        console_write_str("> ");
        if (!console_read(linebuffer,255)){
            break;
        }
        if (strlen(linebuffer) > 0){
            stack_init();
            r = parse_program(linebuffer);
            if (r == PARSER_SYNTAX_ERROR){
                console_write_str("Syntax error\n");
            } else if (r == PARSER_EVAL_ERROR){
                console_write_str("Evaluation error\n");
            }
        }
    }


    return 0;
}
