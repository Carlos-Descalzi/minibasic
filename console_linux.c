#include "console.h"
#include <stdio.h>


void console_write_str(const char* string){
    printf("%s",string);
}
void console_write_chr(const char chr){
    printf("%c",chr);
}
void console_write_int(const int integer){
    printf("%d",integer);
}
int console_read(char* buffer, unsigned char length){
    return fgets(buffer,length, stdin) != NULL;
}
