#include "obstacle.h"

Obstacle obstacles[9];

void renderObstacles() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 9; i++) {
        SDL_Rect rect = { obstacles[i].x, obstacles[i].y - cameraY, OBSTACLE_SIZE, OBSTACLE_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void updateMovingObstacles() {
    for (int i = 6; i < 9; i++) {
        obstacles[i].x += obstacles[i].direction * MOVING_OBSTACLE_SPEED;
        if (obstacles[i].x <= 0 || obstacles[i].x + OBSTACLE_SIZE >= SCREEN_WIDTH) {
            obstacles[i].direction *= -1;
        }
    }
}

bool checkCollision() {
    for (int i = 0; i < 9; i++) {
        if (player.x < obstacles[i].x + OBSTACLE_SIZE &&
            player.x + PLAYER_SIZE > obstacles[i].x &&
            player.y < obstacles[i].y + OBSTACLE_SIZE &&
            player.y + PLAYER_SIZE > obstacles[i].y) {
            return true;
        }
    }
    return false;
}

void setupLevel() {
    player.x = SCREEN_WIDTH / 2 - PLAYER_SIZE / 2;
    player.y = LEVEL_HEIGHT - PLAYER_SIZE;
    player.dx = 0;
    player.dy = 0;
    cameraY = LEVEL_HEIGHT - SCREEN_HEIGHT;

    int yOffset = LEVEL_HEIGHT - SCREEN_HEIGHT + 100;
    obstacles[0] = { SCREEN_WIDTH / 4, yOffset, false, 0 };
    obstacles[1] = { SCREEN_WIDTH / 4, yOffset - 150, false, 0 };
    obstacles[2] = { SCREEN_WIDTH / 4, yOffset - 300, false, 0 };
    obstacles[3] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_SIZE, yOffset, false, 0 };
    obstacles[4] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_SIZE, yOffset - 150, false, 0 };
    obstacles[5] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_SIZE, yOffset - 300, false, 0 };

    obstacles[6] = { SCREEN_WIDTH / 4, yOffset - 600, true, 1 };
    obstacles[7] = { SCREEN_WIDTH / 2, yOffset - 800, true, -1 };
    obstacles[8] = { SCREEN_WIDTH - SCREEN_WIDTH / 4 - OBSTACLE_SIZE, yOffset - 1000, true, 1 };
}
