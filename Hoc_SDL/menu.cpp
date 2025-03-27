#include "menu.h"
#include "game.h"
#include <SDL_image.h>
#include <iostream>

bool gameRunning = false;
SDL_Rect startButton = { 290, 260, 220, 80 }; // Giữ nguyên vùng bấm Start
SDL_Rect quitButton = { 290, 600, 220, 80 };
SDL_Rect levelButton = { 290, 370, 220, 80 };
SDL_Rect optionsButton = { 290, 490, 220, 80 };
SDL_Texture* menuBackground = nullptr; // Ảnh nền menu
SDL_Texture* levelMenuBackground = nullptr; // Background for level selection menu
SDL_Texture* optionsMenuBackground = nullptr; // Ảnh nền options

// 🔹 Load ảnh nền menu
void loadMenuAssets() {
    menuBackground = IMG_LoadTexture(renderer, "menu3.png"); // Đổi thành file của bạn
    if (!menuBackground) {
        std::cout << "Failed to load menu background! Error: " << IMG_GetError() << std::endl;
    }
}
// 🔹 Load ảnh nền menu Level
void loadLevelMenuAssets() {
    levelMenuBackground = IMG_LoadTexture(renderer, "level.png"); // The image you uploaded for the level menu
    if (!levelMenuBackground) {
        std::cout << "Failed to load level menu background! Error: " << IMG_GetError() << std::endl;
    }
}

// Load ảnh nền setting
void loadOptionsMenuAssets() {
    optionsMenuBackground = IMG_LoadTexture(renderer, "options1.png");
    if (!optionsMenuBackground) {
        std::cout << "Failed to load options menu background! Error: " << IMG_GetError() << std::endl;
    }
}

// 🔹 Kiểm tra chuột click vào nút Start
bool isInsideButton(int x, int y) {
    return (x >= startButton.x && x <= startButton.x + startButton.w &&
        y >= startButton.y && y <= startButton.y + startButton.h);
}

bool isQuitButton(int x, int y) {
    return (x >= quitButton.x && x <= quitButton.x + quitButton.w &&
        y >= quitButton.y && y <= quitButton.y + quitButton.h);
}

bool isLevelButton(int x, int y) {
    return (x >= levelButton.x && x <= levelButton.x + levelButton.w &&
        y >= levelButton.y && y <= levelButton.y + levelButton.h);
}

bool isOptionsButton(int x, int y) {
    return (x >= optionsButton.x && x <= optionsButton.x + optionsButton.w &&
        y >= optionsButton.y && y <= optionsButton.y + optionsButton.h);
}


void resetWindow() {
    // 🔹 Đặt lại kích thước cửa sổ về 1400x800 khi vào game
    SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RenderPresent(renderer); // Cập nhật cửa sổ
}

// 🔹 Hiển thị menu trong cửa sổ chung
void showMenu() {
    // 🔹 Đặt cửa sổ menu thành 800x800
    SDL_SetWindowSize(window, 800, 800);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    loadMenuAssets();
    gameRunning = false; // 🔹 Đặt lại gameRunning thành false khi quay lại menu


    bool inMenu = true;
    SDL_Event e;

    while (inMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (isInsideButton(e.button.x, e.button.y)) { // Nhấn vào Play
                    showLevelMenu();
                    inMenu = false; // Thoát menu để vào game
                }
                if (isQuitButton(e.button.x, e.button.y)) {
                    SDL_Quit();
                    exit(0);
                }
                if (isLevelButton(e.button.x, e.button.y)) { // Nhấn vào Level
                    showLevelMenu(); // Mở menu chọn cấp độ
                    return; // Dừng vòng lặp menu chính
                }
                if (isOptionsButton(e.button.x, e.button.y)) { // Nhấn vào "SETTINGS"
                    showOptionsMenu(); // Mở menu Settings
                    return; // Dừng vòng lặp menu chính
                }

            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (menuBackground) {
            SDL_RenderCopy(renderer, menuBackground, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
    }

    // 🔹 Đặt lại kích thước cửa sổ về 1400x800 khi vào game
    resetWindow();

    // 🔹 Giải phóng tài nguyên menu
    SDL_DestroyTexture(menuBackground);
}

void showLevelMenu() {
    SDL_SetWindowSize(window, 800, 800);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    loadLevelMenuAssets();

    bool inLevelMenu = true;
    SDL_Event e;

    SDL_Rect easyButton = { 240, 270, 340, 100 };
    SDL_Rect normalButton = { 240, 410, 340, 100 };
    SDL_Rect hardButton = { 240, 550, 340, 100 };

    while (inLevelMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x, y = e.button.y;
                
                if (x >= easyButton.x && x <= easyButton.x + easyButton.w &&
                    y >= easyButton.y && y <= easyButton.y + easyButton.h) {
                    std::cout << "Easy Mode Selected! Starting game...\n";
                    resetWindow();
                    gameState = LEVEL_1;
                    inLevelMenu = false;

                }
                if (x >= normalButton.x && x <= normalButton.x + normalButton.w &&
                    y >= normalButton.y && y <= normalButton.y + normalButton.h) {
                    std::cout << "Normal Mode Selected! Starting game...\n";
                    gameState = LEVEL_2;
                    resetWindow();
                    inLevelMenu = false;
                }
                if (x >= hardButton.x && x <= hardButton.x + hardButton.w &&
                    y >= hardButton.y && y <= hardButton.y + hardButton.h) {
                    std::cout << "Hard Mode Selected! Starting game...\n";
                    gameState = LEVEL_3;
                    resetWindow();
                    inLevelMenu = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (levelMenuBackground) SDL_RenderCopy(renderer, levelMenuBackground, NULL, NULL);
        SDL_RenderPresent(renderer);

        if (!inLevelMenu) break; // Nếu chọn màn chơi, thoát menu
    }

    // Khi chọn xong level, thoát menu và vào game
    gameRunning = true;
}


void showOptionsMenu() {
    // 🔹 Đặt cửa sổ menu settings thành 800x800
    SDL_SetWindowSize(window, 800, 800);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    loadOptionsMenuAssets(); // Load ảnh nền trước khi hiển thị

    bool inOptionsMenu = true;
    SDL_Event e;

    while (inOptionsMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN) { // Nếu bấm chuột
                inOptionsMenu = false; // Thoát khỏi menu options
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 🔹 Hiển thị ảnh nền menu settings
        if (optionsMenuBackground) {
            SDL_RenderCopy(renderer, optionsMenuBackground, NULL, NULL);
        }
        else {
            std::cout << "Options menu background not loaded!" << std::endl;
        }

        SDL_RenderPresent(renderer);
    }

    // 🔹 Quay lại menu chính
    showMenu();

    // 🔹 Giải phóng tài nguyên
    SDL_DestroyTexture(optionsMenuBackground);
    optionsMenuBackground = nullptr;
}


