#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct file_header {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} file_header;

typedef struct file_info {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} file_info;

typedef struct pixel {
    uint8_t first;
    uint8_t second;
    uint8_t third;
} pixel;
#pragma pack(pop)

pixel **load_bmp(char *in_bmp, file_header *header, file_info *info);

pixel **crop(pixel **image, file_info *info, int32_t new_width, int32_t new_height, int32_t x, int32_t y);

pixel **rotate(pixel **croped_image, int32_t new_width, int32_t new_height);

int save_bmp(char *out_bmp, file_header *header, file_info *info, pixel **rotated_image, int32_t new_width, int32_t new_height);


#endif