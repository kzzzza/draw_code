#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>

// 颜色定义 (ARGB格式)
#define COLOR_RED        0x00FF0000
#define COLOR_GREEN      0x0000FF00
#define COLOR_BLUE       0x000000FF
#define COLOR_WHITE      0x00FFFFFF
#define COLOR_BLACK      0x00000000
#define COLOR_YELLOW     0x00FFFF00
#define COLOR_CYAN       0x0000FFFF
#define COLOR_MAGENTA    0x00FF00FF
#define COLOR_GRAY       0x00808080
#define COLOR_DARKGRAY   0x00404040


// 点结构体
typedef struct {
    int x;
    int y;
} Point;

// 矩形结构体
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

// 初始化/清理函数
int graphics_init(void);
void graphics_cleanup(void);
void graphics_clear(uint32_t color);

// 基本绘图函数
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_rectangle(int x, int y, int width, int height, uint32_t color);
void fill_rectangle(int x, int y, int width, int height, uint32_t color);
void draw_circle(int center_x, int center_y, int radius, uint32_t color);
void fill_circle(int center_x, int center_y, int radius, uint32_t color);
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);

// 工具函数
void graphics_get_resolution(int *width, int *height);

#endif // GRAPHICS_H