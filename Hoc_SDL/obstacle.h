#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include "player.h"

struct Obstacle {
    int x, y;                 // Vị trí
    int currentSize;          // Kích thước hiện tại
    int minSize, maxSize;     // Kích thước tối thiểu và tối đa
    bool expanding;           // Trạng thái co giãn
    int direction;            // Hướng di chuyển
    float angle;              // Góc xoay
};

extern SDL_Texture* customObstacleTextures[4]; // Texture cho 4 vật cản mới
extern SDL_Texture* gearTexture; // Texture bánh răng
extern Obstacle obstacles[13];   // Mở rộng mảng vật cản

const int OBSTACLE_WIDTH = 150;
const int OBSTACLE_HEIGHT = 150;
const int MOVING_OBSTACLE_SPEED = 3;
const int RESIZE_SPEED = 2;

void renderObstacles();
void updateMovingObstacles();
bool checkCollision();
void setupLevel();

#endif