#include "stack.h"
#include "strings.h"
#include <string.h>
#include <stdio.h>

static int stack_index=0;

void stack_init(){
    stack_index = 0;
}

void stack_push_int(int value){
    IMMEDIATE_MEMORY[stack_index].type = VT_INT;
    IMMEDIATE_MEMORY[stack_index++].ivalue = value;
}

void stack_push_str(char* value){
    IMMEDIATE_MEMORY[stack_index].type = VT_STR;
    IMMEDIATE_MEMORY[stack_index++].svalue = strings_store(value);
}

void stack_push(Value* value){
    IMMEDIATE_MEMORY[stack_index++] = *value;
}

int stack_pop(Value* value){
    if (stack_index > 0){
        *value = IMMEDIATE_MEMORY[--stack_index];
        return 1;
    } 
    return 0;
}
