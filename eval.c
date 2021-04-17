#include <stdio.h>
#include "eval.h"

int eval_sum(Value *left, Value* right, Value* result){
    if (left->type == VT_INT && right->type == VT_INT){
        result->type = VT_INT;
        result->ivalue = left->ivalue + right->ivalue;
        return 1;
    }
    return 0;
}
int eval_sub(Value *left, Value* right, Value* result){
    if (left->type == VT_INT && right->type == VT_INT){
        result->type = VT_INT;
        result->ivalue = left->ivalue - right->ivalue;
        return 1;
    }
    return 0;
}
int eval_mul(Value *left, Value* right, Value* result){
    if (left->type == VT_INT && right->type == VT_INT){
        result->type = VT_INT;
        result->ivalue = left->ivalue * right->ivalue;
        return 1;
    }
    return 0;
}
int eval_div(Value *left, Value* right, Value* result){
    if (left->type == VT_INT && right->type == VT_INT){
        result->type = VT_INT;
        result->ivalue = left->ivalue / right->ivalue;
        return 1;
    }
    return 0;
}
