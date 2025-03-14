#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PLAYER_SIZE = 50;
const int OBSTACLE_SIZE = 40;
const float JUMP_FORCE = -12.0f;
const float GRAVITY = 0.5f;
const float MOVE_SPEED = 5.0f;
const int LEVEL_HEIGHT = 2500; 
const int MOVING_OBSTACLE_SPEED = 3;

struct Player {
    float x, y;
    float dx, dy;
};

struct Obstacle {
    int x, y;
    bool moving;
    int direction;
};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* backgroundTexture = nullptr;
Player player;
Obstacle obstacles[9];
int cameraY = 0;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL Init Failed! Error: " << SDL_GetError() << endl;
        return false;
    }
    window = SDL_CreateWindow("Jump Only - SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL_image Init Failed! Error: " << IMG_GetError() << endl;
        return false;
    }
    SDL_Surface* bgSurface = IMG_Load("background.png");
    if (!bgSurface) {
        cout << "Failed to load background image! Error: " << IMG_GetError() << endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    return backgroundTexture != nullptr;
}

void renderBackground() {
    SDL_Rect bgRect = { 0, -cameraY, SCREEN_WIDTH, LEVEL_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect);
}

void renderPlayer() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect rect = { (int)player.x, (int)(player.y - cameraY), PLAYER_SIZE, PLAYER_SIZE };
    SDL_RenderFillRect(renderer, &rect);
}

void renderObstacles() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 9; i++) {
        SDL_Rect rect = { obstacles[i].x, obstacles[i].y - cameraY, OBSTACLE_SIZE, OBSTACLE_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }
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

void updateMovingObstacles() {
    for (int i = 6; i < 9; i++) {
        obstacles[i].x += obstacles[i].direction * MOVING_OBSTACLE_SPEED;
        if (obstacles[i].x <= 0 || obstacles[i].x + OBSTACLE_SIZE >= SCREEN_WIDTH) {
            obstacles[i].direction *= -1;
        }
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

void gameLoop() {
    bool running = true;
    SDL_Event event;
    setupLevel();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleInput(event);
        }
        updatePlayer();
        updateMovingObstacles();
        if (checkCollision()) {
            cout << "Game Over!" << endl;
            running = false;
        }
        if (player.y <= 0) {
            cout << "You win!" << endl;
            running = false;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderBackground();
        renderPlayer();
        renderObstacles();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}

int main(int argc, char* argv[]) {
    if (!init()) return -1;
    gameLoop();
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}