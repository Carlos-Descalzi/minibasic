#ifndef _EVAL_H_
#define _EVAL_H_

#include "common.h"

int eval_sum(Value *left, Value* right, Value* result);
int eval_sub(Value *left, Value* right, Value* result);
int eval_mul(Value *left, Value* right, Value* result);
int eval_div(Value *left, Value* right, Value* result);

#endif
