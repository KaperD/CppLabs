#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"

static const int ROUND = 4;

pixel **load_bmp(char *in_bmp, file_header *header, file_info *info) {
    FILE *fp;
    if ((fp = fopen(in_bmp, "rb")) == NULL) {
        return NULL;
    }
    fread(header, 1, sizeof(*header), fp);
    fread(info, 1, sizeof(*info), fp);
    
    int8_t padding = (ROUND - info->biWidth * sizeof(pixel) % ROUND) % ROUND;

    pixel **image = (pixel **)malloc(info->biHeight * sizeof(pixel*));
    pixel *data = (pixel *)malloc(info->biHeight * info->biWidth * sizeof(pixel));
    if (image == NULL || data == NULL) {
        free(fp);
        return NULL;
    }

    for (int k = 0; k < (int)info->biHeight; k++) {
        image[k] = data + k * info->biWidth;
        fread(image[k], sizeof(pixel), info->biWidth, fp);
        fseek(fp, padding, SEEK_CUR);
    }

    fclose(fp);
    return image;
}

pixel **crop(pixel **image, file_info *info, int32_t new_width, int32_t new_height, int32_t x, int32_t y) {
    pixel **croped_image = (pixel **)malloc(new_height * sizeof(pixel*));
    pixel *data = (pixel *)malloc(new_height * new_width * sizeof(pixel));
    for (int k = 0; k < (int)new_height; k++) {
        croped_image[k] = data + k * new_width;
    }

    int vertical_position = info->biHeight - y - 1;
    int horisontal_position = x;
    for (int k = new_height - 1; k >= 0; k--) {
        horisontal_position = x;
        for (int i = 0; i < (int)new_width; i++) {
            croped_image[k][i] = image[vertical_position][horisontal_position];
            horisontal_position++;
        }
        vertical_position--;
    }
    
    return croped_image;
}

pixel **rotate(pixel **croped_image, int32_t new_width, int32_t new_height) {
    pixel **rotated_image = (pixel **)malloc(new_width * sizeof(pixel *));
    pixel *data = (pixel *)malloc(new_height * new_width * sizeof(pixel));
    for (int k = 0; k < (int)new_width; k++) {
        rotated_image[k] = data + k * new_height;
    }
    
    for (int k = 0; k < (int)new_width; k++) {
        for (int i = 0; i < (int)new_height; i++) {
            rotated_image[k][i] = croped_image[i][new_width - 1 - k];
        }
    }
    
    return rotated_image;
}
int save_bmp(char *out_bmp, file_header *header, file_info *info, pixel **rotated_image, int32_t new_width, int32_t new_height) {
    FILE *fp;
    if ((fp = fopen(out_bmp, "wb")) == NULL) {
        return 1;
    }

    uint8_t padding = (ROUND - (new_height * sizeof(pixel)) % ROUND) % ROUND;

    header->bfSize = new_width * new_height * sizeof(pixel) + new_width * padding + sizeof(*header) + sizeof(*info);
    info->biWidth = new_height;
    info->biHeight = new_width;
    info->biSizeImage = new_width * new_height * sizeof(pixel) + new_width * padding;

    fwrite(header, 1, sizeof(*header), fp);
    fwrite(info, 1, sizeof(*info), fp);

    for (int k = 0; k < new_width; k++) {
        for (int i = 0; i < (int)new_height; i++) {
            fwrite(&rotated_image[k][i], 1, sizeof(pixel), fp);
        }
        for (int o = 0; o < padding; o++) {
            putc(0, fp);
        }
    }

    fclose(fp);
    return 0;
} 