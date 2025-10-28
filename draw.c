// filepath: /home/kz/my_code/draw_code/project/draw.c
#include "draw.h"

// Frame Buffer 相关变量
static int fbfd = -1;
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static char *fbp = NULL;
static long screensize = 0;

// 裁剪区域
static int clip_x = 0, clip_y = 0, clip_width = 0, clip_height = 0;
static bool clipping_enabled = false;

// 初始化图形系统
int graphics_init(void) {
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        return -1;
    }

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        close(fbfd);
        return -1;
    }

    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        close(fbfd);
        return -1;
    }

    screensize = vinfo.yres_virtual * finfo.line_length;
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    
    if ((long)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        close(fbfd);
        return -1;
    }

    printf("Graphics initialized: %dx%d, %dbpp\n", 
           vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
    return 0;
}

// 清理图形系统
void graphics_cleanup(void) {
    if (fbp) {
        munmap(fbp, screensize);
        fbp = NULL;
    }
    if (fbfd != -1) {
        close(fbfd);
        fbfd = -1;
    }
    printf("Graphics cleanup completed.\n");
}

// 获取屏幕分辨率
void graphics_get_resolution(int *width, int *height) {
    if (width) *width = vinfo.xres;
    if (height) *height = vinfo.yres;
}

// 带裁剪检查的像素绘制
void draw_pixel(int x, int y, uint32_t color) {
    if (!fbp) return;
    
    // 检查屏幕边界
    if (x < 0 || x >= (int)vinfo.xres || y < 0 || y >= (int)vinfo.yres)
        return;
    
    // 检查裁剪区域
    if (clipping_enabled) {
        if (x < clip_x || x >= clip_x + clip_width ||
            y < clip_y || y >= clip_y + clip_height)
            return;
    }

    long location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                   (y + vinfo.yoffset) * finfo.line_length;

    if (vinfo.bits_per_pixel == 32) {
        *((uint32_t*)(fbp + location)) = color;
    } else if (vinfo.bits_per_pixel == 16) {
        uint16_t r = (color >> 16) & 0x1F;
        uint16_t g = (color >> 8) & 0x3F;
        uint16_t b = color & 0x1F;
        uint16_t short_color = (r << 11) | (g << 5) | b;
        *((uint16_t*)(fbp + location)) = short_color;
    }
}

// 清屏
void graphics_clear(uint32_t color) {
    if (!fbp) return;
    
    for (int y = 0; y < (int)vinfo.yres; y++) {
        for (int x = 0; x < (int)vinfo.xres; x++) {
            draw_pixel(x, y, color);
        }
    }
}

// 绘制直线 (Bresenham算法)
void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        draw_pixel(x0, y0, color);
        
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// 绘制矩形边框
void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
    draw_line(x, y, x + width, y, color);
    draw_line(x, y + height, x + width, y + height, color);
    draw_line(x, y, x, y + height, color);
    draw_line(x + width, y, x + width, y + height, color);
}

// 填充矩形
void fill_rectangle(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < height; i++) {
        draw_line(x, y + i, x + width, y + i, color);
    }
}

// 绘制圆形 (中点圆算法)
void draw_circle(int center_x, int center_y, int radius, uint32_t color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        draw_pixel(center_x + x, center_y + y, color);
        draw_pixel(center_x + y, center_y + x, color);
        draw_pixel(center_x - y, center_y + x, color);
        draw_pixel(center_x - x, center_y + y, color);
        draw_pixel(center_x - x, center_y - y, color);
        draw_pixel(center_x - y, center_y - x, color);
        draw_pixel(center_x + y, center_y - x, color);
        draw_pixel(center_x + x, center_y - y, color);

        y += 1;
        err += 1 + 2 * y;
        if (2 * (err - x) + 1 > 0) {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}

// 填充圆形
void fill_circle(int center_x, int center_y, int radius, uint32_t color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                draw_pixel(center_x + x, center_y + y, color);
            }
        }
    }
}

// 绘制三角形
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color) {
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x3, y3, color);
    draw_line(x3, y3, x1, y1, color);
}