#include "obstacle.h"
#include "player.h"
#include "tilemap.h"

Obstacle obstacles[9];
SDL_Texture* gearTexture = nullptr;
float gearAngle[9] = { 0 }; // Mảng lưu góc xoay của từng bánh răng
const float ROTATION_SPEED = 5.0f; // Tốc độ xoay

void renderObstacles() {
    for (int i = 0; i < 9; i++) {
        SDL_Rect rect = { obstacles[i].x, obstacles[i].y - cameraY, OBSTACLE_WIDTH, OBSTACLE_HEIGHT };
        SDL_Point center = { OBSTACLE_WIDTH / 2, OBSTACLE_HEIGHT / 2 }; // Tâm xoay

        if (gearTexture != nullptr) {
            SDL_RenderCopyEx(renderer, gearTexture, NULL, &rect, gearAngle[i], &center, SDL_FLIP_NONE);
        }
    }
}

void updateMovingObstacles() {
    for (int i = 6; i < 9; i++) {
        obstacles[i].x += obstacles[i].direction * MOVING_OBSTACLE_SPEED;
        if (obstacles[i].x <= 0 || obstacles[i].x + OBSTACLE_WIDTH >= SCREEN_WIDTH) {
            obstacles[i].direction *= -1;
        }
    }
    // Cập nhật góc xoay
    for (int i = 0; i < 9; i++) {
        gearAngle[i] += ROTATION_SPEED;
        if (gearAngle[i] > 360.0f) {
            gearAngle[i] -= 360.0f;
        }
    }
}

bool checkCollision() {
    // Kiểm tra va chạm với bánh răng (giữ nguyên logic)
    for (int i = 0; i < 9; i++) {
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
            return true; // Game Over khi chạm vào bánh răng
        }
    }

    // Kiểm tra va chạm với tile gai nhọn (chạm bất kỳ góc nào của nhân vật)
    int left = player.x;
    int right = player.x + PLAYER_WIDTH - 1;
    int top = player.y;
    int bottom = player.y + PLAYER_HEIGHT - 1;

    int corners[4][2] = {
        {left, top},        // Góc trên trái
        {right, top},       // Góc trên phải
        {left, bottom},     // Góc dưới trái
        {right, bottom}     // Góc dưới phải
    };

    for (int i = 0; i < 4; i++) {
        int tileX = corners[i][0] / TILE_SIZE;
        int tileY = corners[i][1] / TILE_SIZE;

        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT && tileMap[tileY][tileX] == 2) {
            return true; // Game Over khi chạm vào tile gai nhọn
        }
    }

    return false; // Không có va chạm
}



void setupLevel() {
    player.x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    player.y = LEVEL_HEIGHT - PLAYER_HEIGHT;
    player.dx = 0;
    player.dy = 0;
    cameraY = LEVEL_HEIGHT - SCREEN_HEIGHT;

    int yOffset = LEVEL_HEIGHT - SCREEN_HEIGHT + 100;

    // Vật cản đứng yên
    obstacles[0] = { SCREEN_WIDTH / 4, yOffset, false, 0 };
    obstacles[1] = { SCREEN_WIDTH / 4, yOffset - 150, false, 0 };
    obstacles[2] = { SCREEN_WIDTH / 4, yOffset - 300, false, 0 };
    obstacles[3] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset, false, 0 };
    obstacles[4] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset - 150, false, 0 };
    obstacles[5] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset - 300, false, 0 };

    // Vật cản di chuyển
    obstacles[6] = { SCREEN_WIDTH / 4, yOffset - 600, true, 1 };
    obstacles[7] = { SCREEN_WIDTH / 2, yOffset - 800, true, -1 };
    obstacles[8] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset - 1000, true, 1 };
}