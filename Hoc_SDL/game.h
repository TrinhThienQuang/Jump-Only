#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "player.h"
#include "level.h"

enum GameState {
    MENU,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
};

// Biến toàn cục để theo dõi trạng thái game
extern GameState gameState;


const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;
const int LEVEL_HEIGHT = 4000;


extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* backgroundTexture;
extern SDL_Texture* spikeTexture;
extern SDL_Texture* wallTexture;

extern int cameraY;

bool init();
void renderBackground();
void gameLoop();
void restartGame();
void loadGame();

#endif
