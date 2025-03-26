#include "obstacle.h"
#include "player.h"
#include "tilemap.h"

Obstacle obstacles[13];
SDL_Texture* gearTexture = nullptr;
SDL_Texture* customObstacleTextures[4] = { nullptr }; // 4 vật cản mới
float gearAngle[9] = { 0 }; // Mảng lưu góc xoay của từng bánh răng
const float ROTATION_SPEED = 10.0f; // Tốc độ xoay

void renderObstacles() {
    for (int i = 0; i < 13; i++) {
        SDL_Rect rect = { obstacles[i].x, obstacles[i].y - cameraY, obstacles[i].currentSize, obstacles[i].currentSize };
        SDL_Point center = { obstacles[i].currentSize / 2, obstacles[i].currentSize / 2 };

        if (i < 9 && gearTexture != nullptr) { // Bánh răng (0 - 8)
            SDL_RenderCopyEx(renderer, gearTexture, NULL, &rect, gearAngle[i], &center, SDL_FLIP_NONE);
        }
        else if (i >= 9 && customObstacleTextures[i - 9] != nullptr) { // Vật cản co giãn (9 - 12)
            SDL_RenderCopy(renderer, customObstacleTextures[i - 9], NULL, &rect);
        }
    }
}



void updateMovingObstacles() {
    // Cập nhật vật cản di chuyển ngang (6 - 8)
    for (int i = 6; i < 9; i++) {
        obstacles[i].x += obstacles[i].direction * MOVING_OBSTACLE_SPEED;
        if (obstacles[i].x <= 0 || obstacles[i].x + OBSTACLE_WIDTH >= SCREEN_WIDTH) {
            obstacles[i].direction *= -1; // Đảo hướng khi chạm biên
        }
    }

    // Cập nhật vật cản co giãn (9 - 12)
    for (int i = 9; i < 13; i++) {
        if (obstacles[i].expanding) {
            obstacles[i].currentSize += RESIZE_SPEED;
            if (obstacles[i].currentSize >= obstacles[i].maxSize) {
                obstacles[i].expanding = false; // Chuyển sang trạng thái thu nhỏ
            }
        }
        else {
            obstacles[i].currentSize -= RESIZE_SPEED;
            if (obstacles[i].currentSize <= obstacles[i].minSize) {
                obstacles[i].expanding = true; // Chuyển sang trạng thái giãn nở
            }
        }
    }

    // Cập nhật góc xoay cho bánh răng (0 - 8)
    for (int i = 0; i < 9; i++) {
        gearAngle[i] += ROTATION_SPEED;
        if (gearAngle[i] > 360.0f) {
            gearAngle[i] -= 360.0f; // Đảm bảo góc xoay không vượt quá 360 độ
        }
    }
}


bool checkCollision() {
    // Kiểm tra va chạm với 9 vật thể đầu tiên (giữ nguyên logic hiện tại)
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
            return true; // Va chạm với bánh răng
        }
    }

    // Kiểm tra va chạm với 4 vật thể co giãn (9 - 12)
    for (int i = 9; i < 13; i++) {
        int obstacleCenterX = obstacles[i].x + obstacles[i].currentSize / 2;
        int obstacleCenterY = obstacles[i].y + obstacles[i].currentSize / 2;
        int playerCenterX = player.x + PLAYER_WIDTH / 2;
        int playerCenterY = player.y + PLAYER_HEIGHT / 2;

        int obstacleRadius = obstacles[i].currentSize / 2; // Dùng currentSize để lấy bán kính
        int playerRadius = PLAYER_WIDTH / 3;

        int dx = playerCenterX - obstacleCenterX;
        int dy = playerCenterY - obstacleCenterY;
        int distanceSquared = dx * dx + dy * dy;
        int minDistance = obstacleRadius + playerRadius;

        if (distanceSquared <= minDistance * minDistance) {
            return true; // Va chạm với vật thể co giãn
        }
    }

    // Kiểm tra va chạm với tile gai nhọn (giữ nguyên logic hiện tại)
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
            return true; // Va chạm với tile gai nhọn
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

    // Vật cản cố định (0 - 5)
    obstacles[0] = { SCREEN_WIDTH / 4, yOffset, 150, 50, 200, false, 0 };
    obstacles[1] = { SCREEN_WIDTH / 4, yOffset - 150, 150, 50, 200, false, 0 };
    obstacles[2] = { SCREEN_WIDTH / 4, yOffset - 300, 150, 50, 200, false, 0 };
    obstacles[3] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset, 150, 50, 200, false, 0 };
    obstacles[4] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset - 150, 150, 50, 200, false, 0 };
    obstacles[5] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset - 300, 150, 50, 200, false, 0 };

    // Vật cản di chuyển (6 - 8)
    obstacles[6] = { SCREEN_WIDTH / 4, yOffset - 600, 150, 50, 200, false, 1 };
    obstacles[7] = { SCREEN_WIDTH / 2, yOffset - 800, 150, 50, 200, false, -1 };
    obstacles[8] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_WIDTH, yOffset - 1000, 150, 50, 200, false, 1 };

    // Vật cản co giãn mới (9 - 12)
    obstacles[9] = { 100, yOffset - 1300, 150, 50, 500, true, 0 };
    obstacles[10] = { 1000, yOffset - 1600, 150, 50, 500, true, 0 };
    obstacles[11] = { 100, yOffset - 1900, 150, 50, 500, true, 0 };
    obstacles[12] = { 1000, yOffset - 2200, 150, 50, 500, true, 0 };
}

