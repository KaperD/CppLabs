#include"test_str.h"
#include"str.h"
#include<stdio.h>

int main(void) {
    test_my_strlen();
    test_my_strcpy();
    test_my_strcat();
    test_my_strcmp();

    printf("%s\n", "OK");

    return 0;
}