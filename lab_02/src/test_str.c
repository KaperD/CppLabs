#include"str.h"
#include<assert.h>

void test_my_strlen() {
    char str[] = "three";
    assert(my_strlen(str) == 5);

    char a[] = "";
    assert(my_strlen(a) == 0);

    char b[] = "b";
    assert(my_strlen(b) == 1);

    char c[] = "\0";
    assert(my_strlen(c) == 0);

    return;
}

void test_my_strcpy() {
    char copy[6];
    char src[6] = "qwert";
    my_strcpy(copy, src);
    assert(my_strcmp(copy, src) == 0);

    char copy2[1];
    char src2[] = "";
    my_strcpy(copy2, src2);
    assert(my_strcmp(src2, copy2) == 0);

    return;
}

void test_my_strcat() {
    char a[11];
    for(int k = 0; k < 5; k++) {
        a[k] = 'f';
    }
    a[5] = '\0';
    char b[] = "qwert";
    char c[] = "fffffqwert";
    my_strcat(a, b);
    assert(my_strcmp(a, c) == 0);

    char e[2] = "";
    char f[] = "K";
    my_strcat(e, f);
    assert(my_strcmp(e, f) == 0);
}

void test_my_strcmp() {
    char a[] = "qwert";
    char b[] = "qwert";
    assert(my_strcmp(a, b) == 0);

    char c[] = "qwerz";
    assert(my_strcmp(a, c) == -1);

    char d[] = "q";
    assert(my_strcmp(a, d) == 1);

    char e[] = "z";
    assert(my_strcmp(a, e) == -1);

    char f[] = "";
    char g[] = "";
    assert(my_strcmp(f, g) == 0);

    char h[] = "qwertyui";
    assert(my_strcmp(a, h) == -1);
    assert(my_strcmp(h, a) == 1);
}