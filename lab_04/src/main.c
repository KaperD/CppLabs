#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"mergesort.h"

int int_gt_comparator(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int char_gt_comparator(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

int str_gt_comparator(const void *a, const void *b) {
    return strcmp(*((char**)a), *((char**)b));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    if (!strcmp(argv[1], "str")) {
        char **string = malloc(sizeof(char**)*(argc - 2));
        assert(string != NULL);
        for (int k = 2; k < argc; k++) {
            *(string + k - 2) = argv[k];
        }
        if (mergesort(string, argc - 2, 8, str_gt_comparator) == -1) {
            free(string);
            printf("Error: memory allocation failed\n");
            return 1;
        }
        for (int k = 0; k < argc - 2; k++) {
            printf("%s ", *(string + k));
        }
        free(string);
    } else if (!strcmp(argv[1], "int")) {
        int *a = malloc(sizeof(int)*(argc - 2));
        assert(a != NULL);
        for (int k = 2; k < argc; k++) {
            *(a + k - 2) = atoi(argv[k]);
        }
        if (mergesort(a, argc - 2, sizeof(int), int_gt_comparator) == -1) {
            free(a);
            printf("Error: memory allocation failed\n");
            return 1;
        }
        for (int k = 0; k < argc - 2; k++) {
            printf("%d ", *(a + k));
        }
        free(a);
    } else if (!strcmp(argv[1], "char")) {
        char *a = malloc(argc - 2);
        assert(a != NULL);
        for (int k = 2; k < argc; k++) {
            *(a + k - 2) = *argv[k];
        }
        if (mergesort(a, argc - 2, sizeof(char), char_gt_comparator) == -1) {
            free(a);
            printf("Error: memory allocation failed\n");
            return 1;
        }
        for (int k = 0; k < argc - 2; k++) {
            printf("%c ", *(a + k));
        }
        free(a);
    }

    printf("\n");
    return 0;
}