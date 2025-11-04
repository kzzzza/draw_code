#include "char.h"
HZK16_Font hzk16_font;

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


int load_hzk16_font(const char *filename) {
    struct stat st;
    
    if (stat(filename, &st) != 0) {
        fprintf(stderr, "HZK16字库文件不存在: %s\n", filename);
        return -1;
    }
    
    hzk16_font.size = st.st_size;
    
    hzk16_font.fd = open(filename, O_RDONLY);
    if (hzk16_font.fd < 0) {
        perror("无法打开HZK16字库文件");
        return -1;
    }
    
    hzk16_font.data = (unsigned char *)mmap(0, hzk16_font.size, PROT_READ, MAP_SHARED, hzk16_font.fd, 0);
    if (hzk16_font.data == MAP_FAILED) {
        perror("无法映射HZK16字库文件");
        close(hzk16_font.fd);
        return -1;
    }
    
    printf("HZK16字库加载成功，文件大小: %ld 字节\n", hzk16_font.size);
    return 0;
}

void free_hzk16_font(void) {
    if (hzk16_font.data != NULL && hzk16_font.data != MAP_FAILED) {
        munmap(hzk16_font.data, hzk16_font.size);
        hzk16_font.data = NULL;
    }
    if (hzk16_font.fd >= 0) {
        close(hzk16_font.fd);
        hzk16_font.fd = -1;
    }
}

long get_hzk16_offset(unsigned char area, unsigned char pos) {
    return ((area - 1) * 94 + (pos - 1)) * 32L;
}

void draw_hzk16_char(int x, int y, const unsigned char *gb2312, uint32_t color) {
    unsigned char buffer[32];
    unsigned char area, pos;
    size_t offset;

    area = gb2312[0] - 0xA0;
    pos = gb2312[1] - 0xA0;

    offset = get_hzk16_offset(area, pos);

    if (offset + 32 > hzk16_font.size) {
        // 如果超出范围，用边框表示错误
        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                if (row == 0 || row == 15 || col == 0 || col == 15) {
                    draw_pixel(x + col, y + row, color);
                }
            }
        }
        return;
    }

    memcpy(buffer, hzk16_font.data + offset, 32);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 2; j++) {
            unsigned char byte = buffer[i * 2 + j];
            for (int k = 0; k < 8; k++) {
                if (byte & (0x80 >> k)) {
                    draw_pixel(x + j * 8 + k, y + i, color);
                }
            }
        }
    }
}

void draw_hzk16_string(int x, int y, const unsigned char *gb2312_str, uint32_t color) {
    int cursor_x = x;
    const unsigned char *ptr = gb2312_str;

    while (*ptr != '\0') {
        if (*ptr >= 0xA0 && *(ptr + 1) >= 0xA0) {
            draw_hzk16_char(cursor_x, y, ptr, color);
            cursor_x += 16;
            ptr += 2;
        } else {
            cursor_x += 8;
            ptr += 1;
        }
    }
}