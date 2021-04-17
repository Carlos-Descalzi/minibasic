#ifndef _PARSER_H_
#define _PARSER_H_

#define PARSER_EVAL_ERROR       -2
#define PARSER_SYNTAX_ERROR     -1
#define PARSER_OK               0

int parse_program(char* input_buffer);
int parse_expr(char *input_buffer);
int parse_statements(char* input_buffer);

#endif
