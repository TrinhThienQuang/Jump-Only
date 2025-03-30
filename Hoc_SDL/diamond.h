#ifndef DIAMOND_H
#define DIAMOND_H

#include <SDL.h>
#include "game.h"


struct Diamond {
    SDL_Rect position;
    bool isCollected;
};

// Biến toàn cục
extern SDL_Texture* diamondTexture;
extern SDL_Texture* heartTexture;
extern Diamond diamonds[3];

// Khởi tạo kim cương
void initializeDiamonds();

// Vẽ kim cương
void renderDiamonds();
void renderLives();

// Kiểm tra va chạm giữa người chơi và kim cương
void checkDiamondCollision(const SDL_Rect& player);

void renderCollectedDiamonds();

#endif