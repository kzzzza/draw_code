#ifndef BALL_H
#define BALL_H

#include "draw.h"

// 小球结构体
typedef struct {
    int x, y;           // 小球位置
    int radius;         // 小球半径
    int dx, dy;         // 小球移动方向（速度）
    uint32_t color;     // 小球颜色
} Ball;

// 初始化小球
void ball_init(Ball *ball, int x, int y, int radius, int dx, int dy, uint32_t color);

// 更新小球位置
void ball_update(Ball *ball, int screen_width, int screen_height);

// 绘制小球
void ball_draw(Ball *ball);

#endif // BALL_H