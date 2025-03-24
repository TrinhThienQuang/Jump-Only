#include "obstacle.h"
#include "player.h"

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
    for (int i = 0; i < 9; i++) {
        int obstacleCenterX = obstacles[i].x + OBSTACLE_WIDTH / 2;
        int obstacleCenterY = obstacles[i].y + OBSTACLE_HEIGHT / 2;
        int playerCenterX = player.x + PLAYER_WIDTH / 2;
        int playerCenterY = player.y + PLAYER_HEIGHT / 2;

        // Bán kính bánh răng và bán kính nhân vật (điều chỉnh phù hợp)
        int gearRadius = OBSTACLE_WIDTH / 2;
        int playerRadius = PLAYER_WIDTH / 3; // Giả sử nhân vật nhỏ hơn

        // Tính khoảng cách giữa tâm nhân vật và tâm bánh răng
        int dx = playerCenterX - obstacleCenterX;
        int dy = playerCenterY - obstacleCenterY;
        int distanceSquared = dx * dx + dy * dy;
        int minDistance = gearRadius + playerRadius;

        if (distanceSquared <= minDistance * minDistance) {
            return true; // Game Over khi chạm vào viền bánh răng
        }
    }
    return false;
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