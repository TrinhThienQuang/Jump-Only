#include "diamond.h"
#include <SDL_image.h>


SDL_Texture* diamondTexture = nullptr;
SDL_Texture* heartTexture = nullptr;
Diamond diamonds[3];
int collectedDiamonds = 0;

void initializeDiamonds() {
    collectedDiamonds = 0;
    // Vị trí của kim cương
    if (gameState == LEVEL_1) {
        diamonds[0] = { {670, 6200, 64, 64}, false };
        diamonds[1] = { {1100, 4300, 64, 64}, false };
        diamonds[2] = { {1300, 900, 64, 64}, false };
    }
    else if (gameState == LEVEL_2) {
        diamonds[0] = { {670, 5900, 64, 64}, false };
        diamonds[1] = { {200, 3350, 64, 64}, false };
        diamonds[2] = { {1300, 1180, 64, 64}, false };
    }
    else if (gameState == LEVEL_3) {
        diamonds[0] = { {670, 6150, 64, 64}, false };
        diamonds[1] = { {50, 4200, 64, 64}, false };
        diamonds[2] = { {1300, 1100, 64, 64}, false };
    }
}

void renderDiamonds() {
    for (int i = 0; i < 3; i++) {
        if (!diamonds[i].isCollected) {
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
            collectedDiamonds++;
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