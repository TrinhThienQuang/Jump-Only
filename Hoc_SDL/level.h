#ifndef LEVEL1_H
#define LEVEL1_H

#include <SDL.h>
#include "player.h"
#include "game.h"
#include <vector>

const int TILE_SIZE = 50; // Kích thước mỗi ô vuông
const int MAP_WIDTH = 28; // Số ô theo chiều ngang
const int MAP_HEIGHT = 50; // Số ô theo chiều dọc (LEVEL_HEIGHT / TILE_SIZE)


// Khai báo mảng tileMap1
extern const int tileMap1[MAP_HEIGHT][MAP_WIDTH];
extern const int tileMap2[MAP_HEIGHT][MAP_WIDTH];
extern const int tileMap3[MAP_HEIGHT][MAP_WIDTH];

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
extern std::vector<Obstacle> obstacles;
extern std::vector<float> gearAngle;



const int OBSTACLE_WIDTH = 150;
const int OBSTACLE_HEIGHT = 150;
const int MOVING_OBSTACLE_SPEED = 3;
const int RESIZE_SPEED = 4;
const float ROTATION_SPEED = 10.0f; // Tốc độ xoay

void renderLevel1();
void renderLevel2();
void renderLevel3();
void updateMovingLevel1();
void updateMovingLevel2();
void updateMovingLevel3();
bool checkCollisionLevel1();
bool checkCollisionLevel2();
bool checkCollisionLevel3();
void setupLevel1();
void setupLevel2();
void setupLevel3();





#endif
