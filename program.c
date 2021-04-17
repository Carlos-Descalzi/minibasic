#include "program.h"
#include "common.h"
#include <string.h>
#include "console.h"

void program_add_line(int number, char* program_line){
    ProgramLine* current = PROGRAM_MEMORY;
    ProgramLine* prev = PROGRAM_MEMORY;

    while(current->number != 0){
        prev = current;
        current = current->next;
    }
    current->number = number;
    strncpy(current->code, program_line,strlen(program_line)-1);
    current->next = current + sizeof(ProgramLine) + strlen(current->code);
    memset(current->next,0,sizeof(ProgramLine));
}

void program_list(){
    for (ProgramLine* line = PROGRAM_MEMORY;line->number;line = line->next){
        console_write_int(line->number);
        console_write_chr(' ');
        console_write_str(line->code);
        console_write_chr('\n');
    }
}

ProgramLine* program_find(int number){
    for (ProgramLine* line = PROGRAM_MEMORY; line->number;line = line->next){
        if (line->number == number){
            return line;
        }
    }
    return NULL;
}
