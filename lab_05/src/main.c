#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "point_list.h"

void savetext(intrusive_node *node, void *data) {
    point_node *p = get_point(node);
    fprintf((FILE*)data, "%d %d\n", p->x, p->y);
}

void savebin(intrusive_node *node, void *data) {
    point_node *p = get_point(node);
    fwrite(&(p->x), sizeof(char), 3, (FILE*)data);
    fwrite(&(p->y), sizeof(char), 3, (FILE*)data);
}

void print(intrusive_node *node, void *data) {
    point_node *p = get_point(node);
    printf((char*)data, p->x, p->y);
}

void count(intrusive_node *node, void *data) {
    (void)node;
    (*(int*)data)++;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 0;
    }

    char *load_from = argv[1];
    char *file_name = argv[2];
    char *command = argv[3];

    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);

    FILE *input;
    if (!strcmp(load_from, "loadtext")) {
        input = fopen(file_name, "r");
        if (input == NULL) {
            return 1;
        }
        int x = 0;
        int y = 0;
        while (!feof(input)) {
            fscanf(input, "%d%d", &x, &y);
            if (!feof(input)) {
                add_point(l, x, y);
            }
        }
    } else if (!strcmp(load_from, "loadbin")) {
        input = fopen(file_name, "rb");
        if (input == NULL) {
            return 1;
        }
        int x = 0;
        int y = 0;
        while (!feof(input)) {
            fread(&(x), sizeof(char), 3, input);
            fread(&(y), sizeof(char), 3, input);
            if ((x >> 23) & 1) {
                x |= 0xFF000000;
            }
            if ((y >> 23) & 1) {
                y |= 0xFF000000;
            }
            if (!feof(input)) {
                add_point(l, x, y);
            }
	    x = 0;
 	    y = 0;
        }
    }
    fclose(input);

    if (!strcmp(command, "savetext")) {
        FILE *file = fopen(argv[4], "w");
        if (file != NULL) {
            apply(l, savetext, file);
            fclose(file);
        }
    } else if (!strcmp(command, "savebin")) {
        FILE *file = fopen(argv[4], "wb");
        if (file != NULL) {
            apply(l, savebin, file);
            fclose(file);
        }
    } else if (!strcmp(command, "print")) {
        apply(l, print, argv[4]);
        printf("\n");
    } else if (!strcmp(command, "count")) {
        int x = 0;
        apply(l, count, &x);
        printf("%d", x);
        printf("\n");
    }
    remove_all_points(l);

    return 0;
}
