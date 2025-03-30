#include "diamond.h"
#include <SDL_image.h>

// Định nghĩa biến toàn cục
SDL_Texture* diamondTexture = nullptr;
SDL_Texture* heartTexture = nullptr;
Diamond diamonds[3];

void initializeDiamonds() {
    // Khởi tạo vị trí các kim cương
    diamonds[0] = { {SCREEN_WIDTH / 2 - 16, LEVEL_HEIGHT - SCREEN_HEIGHT + 50, 64, 64}, false };
    diamonds[1] = { {SCREEN_WIDTH / 4 - 50, LEVEL_HEIGHT - SCREEN_HEIGHT - 700, 64, 64}, false };
    diamonds[2] = { {SCREEN_WIDTH - SCREEN_WIDTH / 4 + 50, LEVEL_HEIGHT - SCREEN_HEIGHT - 1800, 64, 64}, false };
}

void renderDiamonds() {
    for (int i = 0; i < 3; i++) {
        if (!diamonds[i].isCollected) { // Chỉ vẽ kim cương chưa thu thập
            SDL_Rect renderRect = {
                diamonds[i].position.x,
                diamonds[i].position.y - cameraY,
                diamonds[i].position.w,
                diamonds[i].position.h
            };
            SDL_RenderCopy(renderer, diamondTexture, nullptr, &renderRect);
        }
    }
}


void checkDiamondCollision(const SDL_Rect& player) {
    for (int i = 0; i < 3; i++) {
        if (!diamonds[i].isCollected && SDL_HasIntersection(&player, &diamonds[i].position)) {
            diamonds[i].isCollected = true;
        }
    }
}

void renderCollectedDiamonds() {
    for (int i = 0; i < 3; i++) {
        if (diamonds[i].isCollected) {
            SDL_Rect collectedPosition = { 10 + i * 60, 70, 50, 50 }; // Vị trí hiển thị
            SDL_RenderCopy(renderer, diamondTexture, nullptr, &collectedPosition);
        }
    }
}

void renderLives() {
    for (int i = 0; i < lives; i++) {
        SDL_Rect heartRect = { i * 60, 10, 80, 50 };
        SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect);
    }
}