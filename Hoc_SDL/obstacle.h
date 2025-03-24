#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include "player.h"

struct Obstacle {
    int x, y;
    bool moving;
    int direction;
};

extern Obstacle obstacles[9];

const int OBSTACLE_SIZE = 40;
const int MOVING_OBSTACLE_SPEED = 3;

void renderObstacles();
void updateMovingObstacles();
bool checkCollision();
void setupLevel();

#endif
