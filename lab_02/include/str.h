#ifndef STR_H
#define STR_H
#include<stddef.h>

size_t my_strlen(const char *s);
//длина строки

char *my_strcpy(char * restrict s1, const char * restrict s2);
//копирование строки

char *my_strcat(char * restrict s1, const char * restrict s2);
//объединение строк

int my_strcmp(const char *s1, const char *s2);
//сравнение строк

#endif