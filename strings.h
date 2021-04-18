#ifndef _STRINGS_H_
#define _STRINGS_H_

#include "common.h"

void strings_init(void);
/**
 * Stores a new string into string table
 * If string already present will reuse existing
 **/
String* strings_store(const char* string);
/**
 * Finds a given string
 **/
String* strings_find(const char* string);
/**
 * Compares a string with a C-string
 **/
int strings_eq(String* string, const char* cstr);
/**
 * Concatenates two strings in a new one
 **/
String* strings_concat(String* str1, String* str2);

#endif
