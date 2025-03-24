#include "player.h"

Player player;

void renderPlayer() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect rect = { (int)player.x, (int)(player.y - cameraY), PLAYER_SIZE, PLAYER_SIZE };
    SDL_RenderFillRect(renderer, &rect);
}

void updatePlayer() {
    player.dy += GRAVITY;
    player.y += player.dy;
    player.x += player.dx;

    if (player.y + PLAYER_SIZE >= LEVEL_HEIGHT) {
        player.y = LEVEL_HEIGHT - PLAYER_SIZE;
        player.dy = 0;
    }

    if (player.y < cameraY + SCREEN_HEIGHT / 2) {
        cameraY = player.y - SCREEN_HEIGHT / 2;
        if (cameraY < 0) cameraY = 0;
    }
}

void handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
            player.dy = JUMP_FORCE;
            player.dx = -MOVE_SPEED;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT) {
            player.dy = JUMP_FORCE;
            player.dx = MOVE_SPEED;
        }
    }
}
