#ifndef _STACK_H_
#define _STACK_H_

#include "common.h"

void stack_init();
void stack_push_int(int value);
void stack_push_str(char* value);
void stack_push(Value* value);
int stack_pop(Value* value);


#endif
