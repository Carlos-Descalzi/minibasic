#ifndef _KEYWORDS_H_
#define _KEYWORDS_H_

typedef struct Keyword {
    char* name;
    int (*handler)(char*);
} Keyword;

extern Keyword KEYWORDS[];



#endif
