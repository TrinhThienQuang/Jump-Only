#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "player.h"
#include "level.h"

enum GameState {
    MENU,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
};

extern GameState gameState;


const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;
const int LEVEL_HEIGHT = 6500;

extern int lives;


extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* backgroundTexture;
extern SDL_Texture* spikeTexture;
extern SDL_Texture* wallTexture;
extern SDL_Rect playerRect; // Biến toàn cục để lưu vị trí của nhân vật
extern int cameraY;
extern Mix_Music* backgroundMusic;
extern Mix_Music* menuMusic;

bool init();
void renderBackground();
void gameLoop();
void restartGame();
void loadGame();
void gameOver();


#endif
