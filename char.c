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

// 显示单个汉字
void draw_hanzi(int x, int y, const char *hanzi, uint32_t color) {
    for (size_t i = 0; i < sizeof(hanzi_fonts) / sizeof(HanziFont); i++) {
        if (strcmp(hanzi_fonts[i].hanzi, hanzi) == 0) {
            const uint8_t *bitmap = hanzi_fonts[i].bitmap;
            for (int row = 0; row < 16; row++) {
                for (int col = 0; col < 16; col++) {
                    if (bitmap[row * 2 + col / 8] & (0x80 >> (col % 8))) {
                        draw_pixel(x + col, y + row, color);
                    }
                }
            }
            return;
        }
    }
}

// 显示汉字字符串
void draw_hanzi_string(int x, int y, const char *str, uint32_t color) {
    while (*str) {
        if ((unsigned char)*str >= 0x80) { // 判断是否为汉字
            draw_hanzi(x, y, str, color);
            str += 3; // UTF-8 汉字占 3 字节
            x += 16; // 每个汉字宽度为 16 像素
        } else {
            draw_char(x, y, *str, color);
            str++;
            x += 8; // ASCII 字符宽度为 8 像素
        }
    }
}