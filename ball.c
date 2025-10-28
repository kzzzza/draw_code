#include "ball.h"


// 初始化小球
void ball_init(Ball *ball, int x, int y, int radius, int dx, int dy, uint32_t color) {
    ball->x = x;
    ball->y = y;
    ball->radius = radius;
    ball->dx = dx;
    ball->dy = dy;
    ball->color = color;
}

// 更新小球位置
void ball_update(Ball *ball, int screen_width, int screen_height) {
    // 更新位置
    ball->x += ball->dx;
    ball->y += ball->dy;

    // 检测边界碰撞
    if (ball->x - ball->radius < 0 || ball->x + ball->radius > screen_width) {
        ball->dx = -ball->dx; // 水平方向反弹
    }
    if (ball->y - ball->radius < 0 || ball->y + ball->radius > screen_height) {
        ball->dy = -ball->dy; // 垂直方向反弹
    }
}

// 绘制小球
void ball_draw(Ball *ball) {
    fill_circle(ball->x, ball->y, ball->radius, ball->color);
}