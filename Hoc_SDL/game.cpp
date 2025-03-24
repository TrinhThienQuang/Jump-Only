#include "game.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* backgroundTexture = nullptr;
int cameraY = 0;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Init Failed! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("Jump Only - SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image Init Failed! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Tải background
    SDL_Surface* bgSurface = IMG_Load("background.png");
    if (!bgSurface) {
        std::cout << "Failed to load background image! Error: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (!backgroundTexture) return false;

    // **Tải nhân vật**
    SDL_Surface* playerSurface = IMG_Load("character.png");
    if (!playerSurface) {
        std::cout << "Failed to load player image! Error: " << IMG_GetError() << std::endl;
        return false;
    }
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_QueryTexture(playerTexture, NULL, NULL, &playerWidth, &playerHeight);
    SDL_FreeSurface(playerSurface);
    if (!playerTexture) {
        std::cout << "Failed to create player texture! Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // Tải vật cản
    SDL_Surface* gearSurface = IMG_Load("obstacle.png");  // Đường dẫn ảnh bánh răng
    if (!gearSurface) {
        std::cout << "Failed to load gear image! Error: " << IMG_GetError() << std::endl;
        return false;
    }
    gearTexture = SDL_CreateTextureFromSurface(renderer, gearSurface);
    SDL_FreeSurface(gearSurface);
    if (!gearTexture) {
        std::cout << "Failed to create gear texture! Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true; // **Chỉ return khi mọi thứ đã được tải xong**
}


void renderBackground() {
    SDL_Rect bgRect = { 0, -cameraY, SCREEN_WIDTH, LEVEL_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect);
}

void gameLoop() {
    bool running = true;
    SDL_Event event;
    setupLevel();
    while(running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleInput(event);
        }

        updatePlayer();
        updateMovingObstacles();

        if (checkCollision()) {
            std::cout << "Game Over!" << std::endl;
            running = false;
        }
        if (player.y <= 0) {
            std::cout << "You win!" << std::endl;
            running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // **Đảm bảo vẽ background trước**
        renderBackground();

        // **Vẽ nhân vật tiếp theo để không bị che**
        renderPlayer();

        // **Sau đó mới vẽ vật cản**
        renderObstacles();


        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

}
