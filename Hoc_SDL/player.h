#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "game.h"

struct Player {
    float x, y;
    float dx, dy;
};

extern Player player;
extern SDL_Texture* playerTexture;
extern int playerWidth, playerHeight;


const int PLAYER_SIZE = 50;
const float JUMP_FORCE = -12.0f;
const float GRAVITY = 0.5f;
const float MOVE_SPEED = 5.0f;
const int PLAYER_WIDTH = 50;  
const int PLAYER_HEIGHT = 50; 

void renderPlayer();
void updatePlayer();
void handleInput(SDL_Event& event);

#endif
