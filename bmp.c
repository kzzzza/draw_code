#include "bmp.h"


// BMP 文件头结构
#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMPFileHeader;

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

// 加载 BMP 图像
BMPImage *bmp_load(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening BMP file");
        return NULL;
    }

    BMPFileHeader fileHeader;
    fread(&fileHeader, sizeof(BMPFileHeader), 1, file);
    if (fileHeader.bfType != 0x4D42) { // 检查 "BM" 标志
        fprintf(stderr, "Error: Not a valid BMP file\n");
        fclose(file);
        return NULL;
    }

    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
        fprintf(stderr, "Error: Only 24-bit or 32-bit BMP files are supported\n");
        fclose(file);
        return NULL;
    }

    int width = infoHeader.biWidth;
    int height = abs(infoHeader.biHeight);
    int row_padded = (width * (infoHeader.biBitCount / 8) + 3) & ~3;

    BMPImage *image = (BMPImage *)malloc(sizeof(BMPImage));
    image->width = width;
    image->height = height;
    image->pixels = (uint32_t *)malloc(width * height * sizeof(uint32_t));

    fseek(file, fileHeader.bfOffBits, SEEK_SET);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t b, g, r, a = 0xFF;
            fread(&b, 1, 1, file);
            fread(&g, 1, 1, file);
            fread(&r, 1, 1, file);
            if (infoHeader.biBitCount == 32) {
                fread(&a, 1, 1, file);
            }
            int pixel_y = (infoHeader.biHeight > 0) ? (height - y - 1) : y; // BMP 像素从下到上存储
            image->pixels[pixel_y * width + x] = (a << 24) | (r << 16) | (g << 8) | b;
        }
        fseek(file, row_padded - width * (infoHeader.biBitCount / 8), SEEK_CUR);
    }

    fclose(file);
    return image;
}

// 释放 BMP 图像
void bmp_free(BMPImage *image) {
    if (image) {
        free(image->pixels);
        free(image);
    }
}

// 显示 BMP 图像
void bmp_draw(int x, int y, BMPImage *image) {
    if (!image) return;

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            uint32_t color = image->pixels[i * image->width + j];
            draw_pixel(x + j, y + i, color);
        }
    }
}