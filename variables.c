#include <stddef.h>
#include "variables.h"
#include "strings.h"

static void do_variable_add(String* name, Value* value);

void variables_add_str(const char* name, const char* value){
    Value svalue;
    svalue.type = VT_STR;
    svalue.svalue = strings_store(value);
    do_variable_add(strings_store(name), &svalue);
}
void variables_add_int(const char* name, int value){
    Value ivalue;
    ivalue.type = VT_INT;
    ivalue.ivalue = value;
    do_variable_add(strings_store(name), &ivalue);
}
void variables_add(Value* name, Value* value){
    do_variable_add(name->svalue,value);
}
static void do_variable_add(String* name, Value* value){
    int i;
    for (i=0; VARIABLE_MEMORY[i].name;i++){
        if (VARIABLE_MEMORY[i].name == name){
            VARIABLE_MEMORY[i].value = *value;
            return;
        }
    }
    VARIABLE_MEMORY[i].name = name;
    VARIABLE_MEMORY[i].value = *value;
}
int variables_get(const char* name, Value* value){
    int i;
    for (i=0;VARIABLE_MEMORY[i].name;i++){
        if (strings_eq(VARIABLE_MEMORY[i].name, name)){
            *value = VARIABLE_MEMORY[i].value;
            return 1;
        }
    }
    return 0;
}
