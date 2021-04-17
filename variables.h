#ifndef _VARIABLES_H_
#define _VARIABLES_H_
#include "common.h"

void variables_add(Value* name, Value* value);
void variables_add_str(const char* name, const char* value);
void variables_add_int(const char* name, int value);
int variables_get(const char* name, Value* value);


#endif
