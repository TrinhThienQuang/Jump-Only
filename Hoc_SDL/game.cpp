﻿#include "game.h"
#include "level.h"
#include "pause.h"
#include "menu.h"
#include "player.h"
#include "diamond.h"

SDL_Window * window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* spikeTexture = nullptr; // Texture cho gai nhọn
SDL_Texture* wallTexture = nullptr;
SDL_Texture* commonObstacleTexture = nullptr;
SDL_Texture* pauseButtonTexture = nullptr; // Thêm texture cho nút Pause
SDL_Texture* gearTexture = nullptr;
int cameraY = 0;
int lives = 1;
SDL_Rect playerRect = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT }; // Giá trị khởi tạo
// Khởi tạo trạng thái game ban đầu là MENU
GameState gameState = MENU;

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
    SDL_Texture* commonObstacleTexture = IMG_LoadTexture(renderer, "gear1.png");
    if (!commonObstacleTexture) {
        std::cout << "Failed to load common obstacle image! Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Gán texture chung cho 4 vật thể mới
    for (int i = 0; i < 4; i++) {
        customObstacleTextures[i] = commonObstacleTexture;
    }

    // tải hiệu ứng nổ
    explosionTexture = IMG_LoadTexture(renderer, "no.png");
    if (!explosionTexture) {
        printf("Failed to load explosion texture: %s\n", SDL_GetError());
    }

    // tải ảnh kim cương
    diamondTexture = IMG_LoadTexture(renderer, "diamond3.png");
    if (!diamondTexture) {
        printf("Failed to load diamond texture : %s\n", SDL_GetError());
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


void rendertileMap(int level) {
    const int (*tileMap)[MAP_WIDTH]; // Con trỏ đến mảng tileMap phù hợp

    // Chọn tileMap theo level
    if (level == LEVEL_1) {
        tileMap = tileMap1;
    }
    else if (level == LEVEL_2) {
        tileMap = tileMap2;
    }
    else if (level == LEVEL_3) {
        tileMap = tileMap3;
    }
    else {
        return; // Level không hợp lệ
    }

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



void loadGame() {
    // Đặt nhân vật về vị trí ở đáy màn hình
    player.x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;  // Giữ nguyên vị trí giữa màn hình
    player.y = LEVEL_HEIGHT - PLAYER_HEIGHT - 50;   // Đặt cách đáy một khoảng an toàn

    player.dx = 0;
    player.dy = 0;

    // Đặt camera để hiển thị đúng phần đáy màn hình
    cameraY = LEVEL_HEIGHT - SCREEN_HEIGHT;
    if (cameraY < 0) cameraY = 0; // Đảm bảo không vượt quá giới hạn
}



void restartGame() {
    // Reset lại trạng thái game
    loadGame();          // Reset vị trí nhân vật và camera
    initializeDiamonds(); // Reset kim cương về trạng thái ban đầu

    isPaused = false;    // Bỏ trạng thái pause
    SDL_Log("Game restarted successfully!");
}



void gameOver() {
    if (lives > 0) {
        lives--;
        restartGame();
    }
    else {
        isGameOver = true;
    }
}





void gameLoop() {
    bool running = true;
    SDL_Event event;

    // Khởi tạo các viên kim cương (chỉ cần làm một lần trước vòng lặp)
    initializeDiamonds();

    if (gameState == LEVEL_1) {
        setupLevel1();
    }
    else if (gameState == LEVEL_2) {
        setupLevel2();
    }
    else {
        setupLevel3();
    }

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
            updateExplosions(); // 🔥 Cập nhật hiệu ứng nổ

            if (gameState == LEVEL_1) {
                updateMovingLevel1();
            }
            else if (gameState == LEVEL_2) {
                updateMovingLevel2();
            }
            else {
                updateMovingLevel3();
            }

            if (gameState == LEVEL_1) {
                if (checkCollisionLevel1()) {
                    std::cout << "Game Over!" << std::endl;
                    running = false;
                }
            }
            else if (gameState == LEVEL_2) {
                if (checkCollisionLevel2()) {
                    std::cout << "Game Over!" << std::endl;
                    running = false;
                }
            }
            else {
                if (checkCollisionLevel3()) {
                    std::cout << "Game Over!" << std::endl;
                    running = false;
                }
            }
            if (player.y <= 0) {
                std::cout << "You win!" << std::endl;
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderBackground();

        if (gameState == LEVEL_1) {
            rendertileMap(1);
        }
        else if (gameState == LEVEL_2) {
            rendertileMap(2);
        }
        else {
            rendertileMap(3);
        }

        renderPlayer();
        renderExplosions(); // 🔥 Vẽ hiệu ứng nổ

        if (gameState == LEVEL_1) {
            renderLevel1();
        }
        else if (gameState == LEVEL_2) {
            renderLevel2();
        }
        else {
            renderLevel3();
        }

        // Gọi hàm vẽ kim cương
        renderDiamonds();
        renderDiamonds();           // Vẽ các kim cương chưa thu thập
        renderCollectedDiamonds();  // Vẽ kim cương đã thu thập

        // Gọi hàm kiểm tra va chạm giữa player và kim cương
        checkDiamondCollision(playerRect);

        if (isGameOver) {
            renderGameOverScreen();
        }
        if (isPaused) {
            if (isOptionsScreen) {
                renderOptionsScreen();
            }
            else {
                renderPauseScreen();
            }
            SDL_RenderPresent(renderer);  // Cập nhật màn hình
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Khoảng thời gian giữa mỗi khung hình
    }
}

