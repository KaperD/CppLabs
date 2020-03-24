#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"

const int MIN_NUMBER_OF_ARGUMENTS = 8;

int main(int argc, char *argv[]) {
    if (argc < MIN_NUMBER_OF_ARGUMENTS) {
        printf("Too few arguments\n");
        return 1;
    }

    char *in_bmp = argv[2];
    char *out_bmp = argv[3];
    int32_t x = atoi(argv[4]);
    int32_t y = atoi(argv[5]);
    int32_t new_width = atoi(argv[6]);
    int32_t new_height = atoi(argv[7]);

    file_header header;
    file_info info; 

    pixel **image = load_bmp(in_bmp, &header, &info);
    if (image == NULL) {
        printf("Can't open file %s\n", in_bmp);
        return 1;
    }
    if (x < 0 || y < 0 || new_width < 1 || new_height < 1 || (uint32_t)(x + new_width) > info.biWidth 
                || (uint32_t)(y + new_height) > info.biHeight) {
        printf("Invalid arguments\n");
        free(image[0]);
        free(image);
        return 1;
    }

    pixel **croped_image = crop(image, &info, new_width, new_height, x, y);
    if (croped_image == NULL) {
        printf("Memory allocation error\n");
        free(image[0]);
        free(image);
        return 1;
    }

    pixel **rotated_image = rotate(croped_image, new_width, new_height);
    if (rotated_image == NULL) {
        printf("Memory allocation error\n");
        free(image[0]);
        free(croped_image[0]);
        free(image);
        free(croped_image);
        return 1;
    }

    if (save_bmp(out_bmp, &header, &info, rotated_image, new_width, new_height)) {
        printf("Can't open file %s\n", out_bmp);
        free(image[0]);
        free(croped_image[0]);
        free(rotated_image[0]);
        free(image);
        free(croped_image);
        free(rotated_image);
        return 1;
    }

    free(image[0]);
    free(croped_image[0]);
    free(rotated_image[0]);
    free(image);
    free(croped_image);
    free(rotated_image);

    return 0;
}
