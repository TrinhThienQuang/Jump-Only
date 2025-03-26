#include "game.h"
#include "tilemap.h"
#include "obstacle.h"
#include "pause.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* spikeTexture = nullptr; // Texture cho gai nhọn
SDL_Texture* wallTexture = nullptr;
SDL_Texture* commonObstacleTexture = nullptr;
SDL_Texture* pauseButtonTexture = nullptr; // Thêm texture cho nút Pause
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
    SDL_Surface* bgSurface = IMG_Load("background5.jpg");
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
    // Tải hình ảnh gai
    spikeTexture = IMG_LoadTexture(renderer, "spike1.png");
    if (!spikeTexture) {
        std::cout << "Failed to load spikes image! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Tải ảnh tường
    wallTexture = IMG_LoadTexture(renderer, "wall.jpg");
    if (!wallTexture) {
        std::cout << "Failed to load wall image! Error: " << IMG_GetError() << std::endl;
        return false;
    }
    // tải nút pause
    SDL_Surface* pauseSurface = IMG_Load("pause.jpg");
    if (!pauseSurface) {
        std::cout << "Failed to load pause button! Error: " << IMG_GetError() << std::endl;
        return false;
    }
    // Tải vật cản
    SDL_Surface* gearSurface = IMG_Load("obstacle.png"); 
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
    // tải vật cản co giãn
    SDL_Texture* commonObstacleTexture = IMG_LoadTexture(renderer, "obstacle.png");
    if (!commonObstacleTexture) {
        std::cout << "Failed to load common obstacle image! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Gán texture chung cho 4 vật thể mới
    for (int i = 0; i < 4; i++) {
        customObstacleTextures[i] = commonObstacleTexture;
    }
    return true; // **Chỉ return khi mọi thứ đã được tải xong**
}


void renderBackground() {
    int img_width, img_height;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &img_width, &img_height);

    for (int x = 0; x < SCREEN_WIDTH; x += img_width) {
        for (int y = -cameraY; y < LEVEL_HEIGHT; y += img_height) {
            SDL_Rect bgRect = { x, y, img_width, img_height };
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect);
        }
    }
}




void renderTileMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE - cameraY, TILE_SIZE, TILE_SIZE };
            if (tileMap[y][x] == 1 && wallTexture != nullptr) {
                SDL_RenderCopy(renderer, wallTexture, NULL, &tileRect);
            }
        }
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE - cameraY, TILE_SIZE, TILE_SIZE };

            // Vẽ gai nhọn (tile 2)
            if (tileMap[y][x] == 2 && spikeTexture != nullptr) {
                double angle = 0.0; // Mặc định hướng lên
                if (y > 0 && tileMap[y - 1][x] == 1) {
                    angle = 180.0; // Gai nhọn hướng xuống
                }
                else if (x > 0 && tileMap[y][x - 1] == 1) {
                    angle = 90.0; // Gai nhọn hướng trái
                }
                else if (x < MAP_WIDTH - 1 && tileMap[y][x + 1] == 1) {
                    angle = 270.0; // Gai nhọn hướng phải
                }
                SDL_RenderCopyEx(renderer, spikeTexture, NULL, &tileRect, angle, NULL, SDL_FLIP_NONE);
            }
        }
    }
}



void gameLoop() {
    bool running = true;
    SDL_Event event;
    setupLevel();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handlePauseEvent(event); // Xử lý ESC để pause

            if (!isPaused) {
                handleInput(event);
            }
        }

        if (!isPaused) {
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
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderBackground();
        renderTileMap();
        renderPlayer();
        renderObstacles();

        if (isPaused) {
            renderPauseScreen(); // Hiển thị màn hình Pause
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}





