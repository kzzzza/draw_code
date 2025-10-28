#include "char.h"

// 显示单个字符
void draw_char(int x, int y, char c, uint32_t color) {
    const uint8_t *bitmap = font_data[(int)c];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (bitmap[i] & (1 << (7 - j))) {
                draw_pixel(x + j, y + i, color);
            }
        }
    }
}

// 显示字符串
void draw_string(int x, int y, const char *str, uint32_t color) {
    int cursor_x = x;
    while (*str) {
        draw_char(cursor_x, y, *str, color);
        cursor_x += 8; // 每个字符宽度为 8 像素
        str++;
    }
}