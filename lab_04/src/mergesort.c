#include"mergesort.h"
#include<assert.h>
#include<stdlib.h>
#include<stddef.h>

static void copy_to_array(char **source, char **destination, size_t element_size) {
    for (int k = 0; k < (int)element_size; k++) {
        **destination = **source;
        (*destination)++;
        (*source)++;
    }
}

static int merge(char *left, char *mid, char *right, size_t element_size, int (*comparator)(const void*, const void*)) {
    char *copy = malloc(right - left);
    if (copy == NULL) {
        return -1;
    }
    char *c = copy;
    char *l = left;
    char *r = mid;
    while (l < mid && r < right) {
        if (comparator(l, r) <= 0) {
            copy_to_array(&l, &copy, element_size);
        } else {
            copy_to_array(&r, &copy, element_size);
        }
    }
    while (l < mid) {
        copy_to_array(&l, &copy, element_size);
    }
    while (r < right) {
        copy_to_array(&r, &copy, element_size);
    }
    copy = c;
    while (left < right) {
        *left = *c;
        left++;
        c++;
    }
    free(copy);
    return 0;
}

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
    char *p = array;
    size_t middle = elements / 2;
    if (elements < 2) return 0;
    mergesort(p, (size_t)(middle), element_size, comparator);
    mergesort(p + (middle) * element_size, 
            (size_t)(elements - middle), element_size, comparator);
    if (merge(array, p + (middle) * element_size, 
        p + elements * element_size, element_size, comparator) == -1) {
            return -1;
    }
    return 0;
}