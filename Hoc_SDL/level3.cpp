#include "level.h"
#include "player.h"
#include "game.h"
#include <vector>

void initLevel3() {
    gearAngle.clear();
    gearAngle.resize(33, 0.0f);
    obstacles.clear();
    obstacles.resize(33);
}

void renderLevel3() {
    for (int i = 0; i < 33; i++) {
        SDL_Rect rect = { obstacles[i].x, obstacles[i].y - cameraY, obstacles[i].currentSize, obstacles[i].currentSize };
        SDL_Point center = { obstacles[i].currentSize / 2, obstacles[i].currentSize / 2 };
        if (i < 29 && gearTexture != nullptr) {
            SDL_RenderCopyEx(renderer, gearTexture, NULL, &rect, gearAngle[i], &center, SDL_FLIP_NONE);
        }
        else if (i >= 29 && customObstacleTextures[i - 29] != nullptr) {
            SDL_RenderCopy(renderer, customObstacleTextures[i - 29], NULL, &rect);
        }
    }
}

void updateMovingLevel3() {
    for (int i = 14; i < 29; i++) {
        obstacles[i].x += obstacles[i].direction * MOVING_OBSTACLE_SPEED;
        if (obstacles[i].x <= 0 || obstacles[i].x + OBSTACLE_WIDTH >= SCREEN_WIDTH) {
            obstacles[i].direction *= -1;
        }
    }

    for (int i = 29; i < 33; i++) {
        if (obstacles[i].expanding) {
            obstacles[i].currentSize += RESIZE_SPEED;
            if (i == 30 || i == 32) {
                obstacles[i].x -= RESIZE_SPEED;
            }
            if (obstacles[i].currentSize >= obstacles[i].maxSize) {
                obstacles[i].expanding = false;
            }
        }
        else {
            obstacles[i].currentSize -= RESIZE_SPEED;
            if (i == 30 || i == 32) {
                obstacles[i].x += RESIZE_SPEED;
            }

            if (obstacles[i].currentSize <= obstacles[i].minSize) {
                obstacles[i].expanding = true;
            }
        }
    }
    for (int i = 0; i < 29; i++) {
        gearAngle[i] += ROTATION_SPEED;
        if (gearAngle[i] > 360.0f) {
            gearAngle[i] -= 360.0f;
        }
    }
}

void setupLevel3() {
    player.x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    player.y = LEVEL_HEIGHT - PLAYER_HEIGHT;
    player.dx = 0;
    player.dy = 0;
    cameraY = LEVEL_HEIGHT - SCREEN_HEIGHT;

    int yOffset = LEVEL_HEIGHT - SCREEN_HEIGHT + 100;

    // Hàng 1 (trên cùng) - 5 vật cản
    obstacles[0] = { SCREEN_WIDTH / 10 * 1 - 75, yOffset - 0,     150, 50, 0, false, 0 };
    obstacles[1] = { SCREEN_WIDTH / 10 * 3 - 75, yOffset - 0,     150, 50, 0, false, 0 };
    obstacles[2] = { SCREEN_WIDTH / 10 * 5 - 75, yOffset - 0,     150, 50, 0, false, 0 };
    obstacles[3] = { SCREEN_WIDTH / 10 * 7 - 75, yOffset - 0,     150, 50, 0, false, 0 };
    obstacles[4] = { SCREEN_WIDTH / 10 * 9 - 75, yOffset - 0,     150, 50, 0, false, 0 };

    // Hàng 2 (ở giữa, lệch phải) - 4 vật cản
    obstacles[5] = { SCREEN_WIDTH / 10 * 2 - 75, yOffset - 200,   150, 50, 0, false, 0 };
    obstacles[6] = { SCREEN_WIDTH / 10 * 4 - 75, yOffset - 200,   150, 50, 0, false, 0 };
    obstacles[7] = { SCREEN_WIDTH / 10 * 6 - 75, yOffset - 200,   150, 50, 0, false, 0 };
    obstacles[8] = { SCREEN_WIDTH / 10 * 8 - 75, yOffset - 200,   150, 50, 0, false, 0 };

    // Hàng 3 (dưới cùng) - 5 vật cản
    obstacles[9] = { SCREEN_WIDTH / 10 * 1 - 75, yOffset - 400,   150, 50, 0, false, 0 };
    obstacles[10] = { SCREEN_WIDTH / 10 * 3 - 75, yOffset - 400,   150, 50, 0, false, 0 };
    obstacles[11] = { SCREEN_WIDTH / 10 * 5 - 75, yOffset - 400,   150, 50, 0, false, 0 };
    obstacles[12] = { SCREEN_WIDTH / 10 * 7 - 75, yOffset - 400,   150, 50, 0, false, 0 };
    obstacles[13] = { SCREEN_WIDTH / 10 * 9 - 75, yOffset - 400,   150, 50, 0, false, 0 };


    // Hàng 1
    obstacles[14] = { SCREEN_WIDTH / 6 - 75,        yOffset - 900, 150, 50, 200, false,  1 };
    obstacles[15] = { SCREEN_WIDTH / 6 * 2 - 75,    yOffset - 900, 150, 50, 200, false, -1 };
    obstacles[16] = { SCREEN_WIDTH / 6 * 3 - 75,    yOffset - 900, 150, 50, 200, false,  1 };
    obstacles[17] = { SCREEN_WIDTH / 6 * 4 - 75,    yOffset - 900, 150, 50, 200, false, -1 };
    obstacles[18] = { SCREEN_WIDTH / 6 * 5 - 75,    yOffset - 900, 150, 50, 200, false,  1 };

    // Hàng 2
    obstacles[19] = { SCREEN_WIDTH / 6 - 75,        yOffset - 1200, 150, 50, 200, false, -1 };
    obstacles[20] = { SCREEN_WIDTH / 6 * 2 - 75,    yOffset - 1200, 150, 50, 200, false,  1 };
    obstacles[21] = { SCREEN_WIDTH / 6 * 3 - 75,    yOffset - 1200, 150, 50, 200, false, -1 };
    obstacles[22] = { SCREEN_WIDTH / 6 * 4 - 75,    yOffset - 1200, 150, 50, 200, false,  1 };
    obstacles[23] = { SCREEN_WIDTH / 6 * 5 - 75,    yOffset - 1200, 150, 50, 200, false, -1 };

    // Hàng 3
    obstacles[24] = { SCREEN_WIDTH / 6 - 75,        yOffset - 1500, 150, 50, 200, false,  1 };
    obstacles[25] = { SCREEN_WIDTH / 6 * 2 - 75,    yOffset - 1500, 150, 50, 200, false, -1 };
    obstacles[26] = { SCREEN_WIDTH / 6 * 3 - 75,    yOffset - 1500, 150, 50, 200, false,  1 };
    obstacles[27] = { SCREEN_WIDTH / 6 * 4 - 75,    yOffset - 1500, 150, 50, 200, false, -1 };
    obstacles[28] = { SCREEN_WIDTH / 6 * 5 - 75,    yOffset - 1500, 150, 50, 200, false,  1 };



    // vật cản giãn nở
    obstacles[29] = { 0, yOffset - 2500, 150, 300, 1000, true, 0 };
    obstacles[30] = { 1300, yOffset - 3000, 150, 300, 1000, true, 0 };
    obstacles[31] = { 0, yOffset - 3500, 150, 300, 1000, true, 0 };
    obstacles[32] = { 1300, yOffset - 4000, 150, 300, 1000, true, 0 };
}

bool checkCollisionLevel3() {
    for (int i = 0; i < 29; i++) {
        int obstacleCenterX = obstacles[i].x + OBSTACLE_WIDTH / 2;
        int obstacleCenterY = obstacles[i].y + OBSTACLE_HEIGHT / 2;
        int playerCenterX = player.x + PLAYER_WIDTH / 2;
        int playerCenterY = player.y + PLAYER_HEIGHT / 2;
        int gearRadius = OBSTACLE_WIDTH / 2;
        int playerRadius = PLAYER_WIDTH / 3;
        int dx = playerCenterX - obstacleCenterX;
        int dy = playerCenterY - obstacleCenterY;
        int distanceSquared = dx * dx + dy * dy;
        int minDistance = gearRadius + playerRadius;

        if (distanceSquared <= minDistance * minDistance) {
            addExplosion(player.x, player.y);
            gameOver();

        }
    }
    for (int i = 29; i < 33; i++) {
        int obstacleCenterX = obstacles[i].x + obstacles[i].currentSize / 2;
        int obstacleCenterY = obstacles[i].y + obstacles[i].currentSize / 2;
        int playerCenterX = player.x + PLAYER_WIDTH / 2;
        int playerCenterY = player.y + PLAYER_HEIGHT / 2;

        int obstacleRadius = obstacles[i].currentSize / 2;
        int playerRadius = PLAYER_WIDTH / 3;

        int dx = playerCenterX - obstacleCenterX;
        int dy = playerCenterY - obstacleCenterY;
        int distanceSquared = dx * dx + dy * dy;
        int minDistance = obstacleRadius + playerRadius;

        if (distanceSquared <= minDistance * minDistance) {
            addExplosion(player.x, player.y);
            gameOver();

        }
    }
    int left = player.x;
    int right = player.x + PLAYER_WIDTH - 1;
    int top = player.y;
    int bottom = player.y + PLAYER_HEIGHT - 1;

    int corners[4][2] = {
        {left, top},
        {right, top},
        {left, bottom},
        {right, bottom}
    };

    for (int i = 0; i < 4; i++) {
        int tileX = corners[i][0] / TILE_SIZE;
        int tileY = corners[i][1] / TILE_SIZE;

        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT && tileMap2[tileY][tileX] == 2) {
            addExplosion(player.x, player.y);
            gameOver();

        }
    }

    return false;
}


const int tileMap3[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0},
    {2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 0},
    {2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 2, 0, 0, 2, 1, 1, 0},
    {0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};