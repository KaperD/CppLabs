#include"str.h"
#include<stddef.h>

//длина строки
size_t my_strlen(const char *s) {
    size_t len = 0;
    while (*s) {
        len++;
        s++;
    }

    return len;
}

//копирование строки
char *my_strcpy(char * restrict s1, const char * restrict s2) {
    char *t = s1;
    while (*s2) {
        *t = *s2;
        t++;
        s2++;
    }
    *t = '\0';
    
    return s1;
}

//объединение строк
char *my_strcat(char * restrict s1, const char * restrict s2) {
    char *t = s1;
    t += my_strlen(s1);
    my_strcpy(t, s2);

    return s1;
}

//сравнение строк
int my_strcmp(const char *s1, const char *s2) {
    while (*s1 || *s2) {
        if (*s1 > *s2) {
            return 1;
        }
        if (*s1 < *s2) {
            return -1;
        }
        s1++;
        s2++;
    }
    return 0;
}
