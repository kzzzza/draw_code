// filepath: /home/kz/my_code/draw_code/project/main.c
#include "draw.h"
#include "bmp.h"
#include "char.h"
#include "ball.h"

int main() {
    int width, height;
    
    // 初始化图形系统
    if (graphics_init() != 0) {
        fprintf(stderr, "Failed to initialize graphics\n");
        return 1;
    }
    
    // 获取屏幕分辨率
    graphics_get_resolution(&width, &height);
    printf("Screen resolution: %dx%d\n", width, height);
    
    // ==================== 功能1: 绘制基本图形 ====================
    printf("Drawing basic shapes...\n");
    
    // 清屏为深蓝色背景
    graphics_clear(0x00102040);  // 深蓝色
    
    // 绘制网格背景
    for (int i = 0; i < width; i += 20) {
        draw_line(i, 0, i, height, 0x00204060);  // 竖线
    }
    for (int i = 0; i < height; i += 20) {
        draw_line(0, i, width, i, 0x00204060);  // 横线
    }
    
    // 绘制各种基本图形
    draw_rectangle(50, 50, 100, 80, COLOR_RED);           // 红色矩形边框
    fill_rectangle(180, 50, 100, 80, COLOR_GREEN);        // 填充绿色矩形
    draw_circle(350, 90, 40, COLOR_BLUE);                 // 蓝色圆形边框
    fill_circle(480, 90, 40, COLOR_YELLOW);               // 填充黄色圆形
    draw_triangle(600, 50, 550, 130, 650, 130, COLOR_CYAN); // 青色三角形
    sleep(3); // 显示5秒后清屏
    // ==================== 功能2: 加载并显示 BMP 图像 ====================
    printf("Loading and displaying BMP image...\n");
    BMPImage *image = bmp_load("image.bmp");
    if (image) {
        bmp_draw((width - image->width) / 2, (height - image->height) / 2, image);
        bmp_free(image);
    } else {
        fprintf(stderr, "Failed to load BMP image\n");
    }   
    sleep(3); // 显示5秒后清屏
    graphics_clear(COLOR_YELLOW);

    // ==================== 功能3: 显示字符和字符串 ====================
    printf("Displaying characters and strings...\n");
    draw_string(50, height - 100, "231180007YKY!", COLOR_BLACK);
    draw_char(50, height - 70, 'N', COLOR_BLACK);
    draw_char(70, height - 70, 'J', COLOR_BLACK);
    draw_char(90, height - 70, 'U', COLOR_BLACK);

    // ==================== 功能4: 显示汉字字符串 ====================
    printf("Displaying Chinese characters...\n");
    draw_hanzi_string(100, height - 100, "你好，世界！", COLOR_BLACK);
    draw_hanzi_string(100, height - 70, "杨凯越，南京大学", COLOR_BLACK);

    // ==================== 功能5: 小球动画 ====================
    sleep(10); // 暂停10秒，准备显示小球动画

    graphics_clear(0x00000000);

    Ball ball;
    ball_init(&ball, 400, 300, 20, 5, 3, COLOR_RED);

    // 动画循环
    for(int i=0; i<600; i++) {
        // 更新小球位置
        ball_update(&ball, width, height);

        // 绘制小球
        ball_draw(&ball);

        // 延迟 16 毫秒（约 60 FPS）
        usleep(16000);
    }


    // 清理图形系统
    graphics_cleanup();
    
    printf("Program completed successfully.\n");
    return 0;
}