#ifndef BMP_H
#define BMP_H

#include "draw.h"

// BMP 图像结构
typedef struct {
    int width;
    int height;
    uint32_t *pixels; // 像素数据 (每个像素为 32 位 ARGB 格式)
} BMPImage;

// 加载 BMP 图像
BMPImage *bmp_load(const char *filename);

// 释放 BMP 图像
void bmp_free(BMPImage *image);

// 显示 BMP 图像
void bmp_draw(int x, int y, BMPImage *image);

#endif // BMP_H