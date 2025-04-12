#ifndef DIAMOND_H
#define DIAMOND_H

#include <SDL.h>
#include "game.h"


struct Diamond {
    SDL_Rect position;
    bool isCollected;
};

extern SDL_Texture* diamondTexture;
extern SDL_Texture* heartTexture;
extern Diamond diamonds[3];
extern int collectedDiamonds;

void initializeDiamonds();
void renderDiamonds();
void renderLives();
void checkDiamondCollision(const SDL_Rect& player);
void renderCollectedDiamonds();

#endif