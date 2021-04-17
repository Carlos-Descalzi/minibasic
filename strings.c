#include <stdio.h>
#include <string.h>
#include "strings.h"
#include "common.h"

String* last_pos;

static String* strings_next(String* string);

void strings_init(){
    last_pos = (String*)STRING_MEMORY;
}

String* strings_store(const char* cstr){
    String* str;
    int l;

    str = strings_find(cstr);

    if (str){
        return str;
    }
    l = strlen(cstr);
    last_pos->length = l;
    memcpy(last_pos->string,cstr,l);
    str = last_pos;
    last_pos = (String*)(((char*)last_pos)+l+1);

    return str;
}

String* strings_find(const char* cstr){
    String* current = (String*)STRING_MEMORY;

    while(current != last_pos){
        if (strings_eq(current, cstr)){
            return current;
        }
        current = strings_next(current);
    }
    return NULL;
}

int strings_eq(String* string, const char* cstr){
    return strlen(cstr) == string->length && !strncmp(string->string,cstr,strlen(cstr));
}

static String* strings_next(String* string){
    return (String*)(((char*)string)+1+string->length);
}
