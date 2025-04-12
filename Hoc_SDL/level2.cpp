#include "level.h"
#include "player.h"
#include "game.h"
#include <vector>

void initLevel2() {
    gearAngle.clear();
    gearAngle.resize(19, 0.0f);  // Đổi số phần tử khi sang level 2
    obstacles.clear();  // Xóa các phần tử cũ trước khi khởi tạo level 1
    obstacles.resize(19); // Ví dụ: Level 1 có 5 vật cản
}

void renderLevel2() {
    for (int i = 0; i < 19; i++) {
        SDL_Rect rect = { obstacles[i].x, obstacles[i].y - cameraY, obstacles[i].currentSize, obstacles[i].currentSize };
        SDL_Point center = { obstacles[i].currentSize / 2, obstacles[i].currentSize / 2 };
        if (i < 15 && gearTexture != nullptr) { // Bánh răng (0 - 8)
            SDL_RenderCopyEx(renderer, gearTexture, NULL, &rect, gearAngle[i], &center, SDL_FLIP_NONE);
        }
        else if (i >= 15 && customObstacleTextures[i - 15] != nullptr) { // Vật cản co giãn (9 - 12)
            SDL_RenderCopy(renderer, customObstacleTextures[i - 15], NULL, &rect);
        }
    }
}

void updateMovingLevel2() {
    // Cập nhật vật cản di chuyển (9 - 14)
    for (int i = 9; i < 15; i++) {
        obstacles[i].x += obstacles[i].direction * MOVING_OBSTACLE_SPEED;
        if (obstacles[i].x <= 0 || obstacles[i].x + OBSTACLE_WIDTH >= SCREEN_WIDTH) {
            obstacles[i].direction *= -1; // Đảo chiều di chuyển khi chạm biên
        }
    }

    for (int i = 15; i < 19; i++) {
        if (obstacles[i].expanding) {
            obstacles[i].currentSize += RESIZE_SPEED;

            if (i == 15 || i == 17) {
                // Vật cản bên trái -> Giãn ra bên phải
                // (Giữ nguyên x, chỉ tăng currentSize)
            }
            else if (i == 16 || i == 18) {
                // Vật cản bên phải -> Giãn ra bên trái
                obstacles[i].x -= RESIZE_SPEED;
            }

            if (obstacles[i].currentSize >= obstacles[i].maxSize) {
                obstacles[i].expanding = false; // Chuyển sang trạng thái thu nhỏ
            }
        }
        else {
            obstacles[i].currentSize -= RESIZE_SPEED;

            if (i == 15 || i == 17) {
                // Vật cản bên trái -> Thu nhỏ về trái
                // (Giữ nguyên x, chỉ giảm currentSize)
            }
            else if (i == 16 || i == 18) {
                // Vật cản bên phải -> Thu nhỏ về phải
                obstacles[i].x += RESIZE_SPEED;
            }

            if (obstacles[i].currentSize <= obstacles[i].minSize) {
                obstacles[i].expanding = true; // Chuyển sang trạng thái giãn nở
            }
        }
    }
    // Cập nhật góc quay cho các vật cản cố định (0 - 8)
    for (int i = 0; i < 15; i++) {
        gearAngle[i] += ROTATION_SPEED;
        if (gearAngle[i] > 360.0f) {
            gearAngle[i] -= 360.0f; // Đảm bảo góc không vượt quá 360 độ
        }
    }
}

void setupLevel2() {
    player.x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    player.y = LEVEL_HEIGHT - PLAYER_HEIGHT;
    player.dx = 0;
    player.dy = 0;
    cameraY = LEVEL_HEIGHT - SCREEN_HEIGHT;

    int yOffset = LEVEL_HEIGHT - SCREEN_HEIGHT + 100;

    // Vật cản cố định (0 - 8)
    // Hàng 1
    obstacles[0] = { SCREEN_WIDTH / 6 - 75, yOffset, 150, 50, 200, false, 0 };
    obstacles[1] = { SCREEN_WIDTH / 2 - 75, yOffset, 150, 50, 200, false, 0 };
    obstacles[2] = { SCREEN_WIDTH * 5 / 6 - 75, yOffset, 150, 50, 200, false, 0 };
    obstacles[3] = { SCREEN_WIDTH / 6 - 75, yOffset - 300, 150, 50, 200, false, 0 };
    obstacles[4] = { SCREEN_WIDTH / 2 - 75, yOffset - 300, 150, 50, 200, false, 0 };
    obstacles[5] = { SCREEN_WIDTH * 5 / 6 - 75, yOffset - 300, 150, 50, 200, false, 0 };
    obstacles[6] = { SCREEN_WIDTH / 6 - 75, yOffset - 600, 150, 50, 200, false, 0 };
    obstacles[7] = { SCREEN_WIDTH / 2 - 75, yOffset - 600, 150, 50, 200, false, 0 };
    obstacles[8] = { SCREEN_WIDTH * 5 / 6 - 75, yOffset - 600, 150, 50, 200, false, 0 };

    // Vật cản di chuyển 
    obstacles[9] = { SCREEN_WIDTH / 6 - 75, yOffset - 1000, 150, 50, 200, false, 1 };
    obstacles[10] = { SCREEN_WIDTH * 5 / 6 - 75, yOffset - 1000, 150, 50, 200, false, -1 };
    obstacles[11] = { SCREEN_WIDTH / 6 - 75, yOffset - 1300, 150, 50, 200, false, -1 };
    obstacles[12] = { SCREEN_WIDTH * 5 / 6 - 75, yOffset - 1300, 150, 50, 200, false, 1 };
    obstacles[13] = { SCREEN_WIDTH / 6 - 75, yOffset - 1700, 150, 50, 200, false, 1 };
    obstacles[14] = { SCREEN_WIDTH * 5 / 6 - 75, yOffset - 1700, 150, 50, 200, false, -1 };

    // Vật cản co giãn mới (9 - 12)
    obstacles[15] = { 0, yOffset - 2500, 150, 300, 800, true, 0 };  // vị trí và kích thước minSize, maxSize
    obstacles[16] = { 1300, yOffset - 3000, 150, 300, 800, true, 0 };
    obstacles[17] = { 0, yOffset - 3500, 150, 300, 800, true, 0 };
    obstacles[18] = { 1300, yOffset - 4000, 150, 300, 800, true, 0 };
}

bool checkCollisionLevel2() {
    // Kiểm tra va chạm với 9 vật thể đầu tiên (giữ nguyên logic hiện tại)
    for (int i = 0; i < 15; i++) {
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

    // Kiểm tra va chạm với 4 vật thể co giãn (9 - 12)
    for (int i = 15; i < 19; i++) {
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
            addExplosion(player.x, player.y);
            gameOver();

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

        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT && tileMap2[tileY][tileX] == 2) {
            addExplosion(player.x, player.y);
            gameOver();

        }
    }

    return false; // Không có va chạm
}


const int tileMap2[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0},
    {1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
    {1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1},
    {1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1},
};