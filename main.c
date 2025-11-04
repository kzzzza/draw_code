#include "draw.h"
#include "bmp.h"
#include "char.h"
#include "ball.h"

int main() {
    int width, height;
    
    //初始化图形系统
    if (graphics_init() != 0) {
        fprintf(stderr, "Failed to initialize graphics\n");
        return 1;
    }

    //加载汉字库
    if (load_hzk16_font("HZK16") != 0) {
        graphics_cleanup();
        return 1;
    }

    // 获取屏幕分辨率
    graphics_get_resolution(&width, &height);
    printf("Screen resolution: %dx%d\n", width, height);

    // ==================== 绘制1: 基本形状 ====================
    printf("Drawing basic shapes...\n");

    // 设置背景色
    graphics_clear(0x00102040);  // 深蓝色

    // 绘制网格
    for (int i = 0; i < width; i += 20) {
        draw_line(i, 0, i, height, 0x00204060);  // 浅蓝色
    }
    for (int i = 0; i < height; i += 20) {
        draw_line(0, i, width, i, 0x00204060);  // 浅蓝色
    }

    // 绘制矩形
    draw_rectangle(50, 50, 100, 80, COLOR_RED);           // 红色矩形
    fill_rectangle(180, 50, 100, 80, COLOR_GREEN);        // 绿色填充矩形
    draw_circle(350, 90, 40, COLOR_BLUE);                 // 蓝色圆形
    fill_circle(480, 90, 40, COLOR_YELLOW);               // 黄色圆形
    draw_triangle(600, 50, 550, 130, 650, 130, COLOR_CYAN); // 青色三角形
    sleep(3); // 显示5秒钟
    // ==================== 绘制2: 显示BMP图像 ====================
    printf("Loading and displaying BMP image...\n");
    BMPImage *image = bmp_load("image.bmp");
    if (image) {
        bmp_draw((width - image->width) / 2, (height - image->height) / 2, image);
        bmp_free(image);
    } else {
        fprintf(stderr, "Failed to load BMP image\n");
    }   
    sleep(3); // 显示3秒钟
    graphics_clear(COLOR_YELLOW);
    
    // ==================== 绘制3: 显示字符和字符串 ====================
    printf("Displaying characters and strings...\n");
    draw_string(50, height - 100, "231180007YKY!", COLOR_BLACK);
    draw_char(50, height - 70, 'N', COLOR_BLACK);
    draw_char(70, height - 70, 'J', COLOR_BLACK);
    draw_char(90, height - 70, 'U', COLOR_BLACK);

    // ==================== 绘制4: 显示汉字 ====================
    printf("Displaying Chinese characters...\n");
    draw_hzk16_string(100, 100, (const unsigned char *)"南京大学电子学院杨凯越", COLOR_BLACK);

    // ==================== 绘制5: 显示动画 ====================
    sleep(10); // 暂停10秒钟准备显示动画

    graphics_clear(0x00000000);


    Ball ball;
    ball_init(&ball, 400, 300, 20, 5, 3, COLOR_RED);

    // 开始动画
    for(int i=0; i<600; i++) {
        // 更新球的位置
        ball_update(&ball, width, height);

        // 绘制球
        ball_draw(&ball);

        // 暂停 16 毫秒以达到 60 FPS
        usleep(16000);
    }


    // 结束动画
    graphics_cleanup();
    // 释放汉字库
    free_hzk16_font();
    
    printf("Program completed successfully.\n");
    return 0;
}