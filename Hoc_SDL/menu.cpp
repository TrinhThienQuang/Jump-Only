#include "menu.h"
#include "game.h"
#include <SDL_image.h>
#include <iostream>

bool gameRunning = false;
SDL_Rect startButton = { 170, 200, 450, 100 }; // Giữ nguyên vùng bấm Start
SDL_Texture* menuBackground = nullptr; // Ảnh nền menu

// 🔹 Load ảnh nền menu
void loadMenuAssets() {
    menuBackground = IMG_LoadTexture(renderer, "menu.png"); // Đổi thành file của bạn
    if (!menuBackground) {
        std::cout << "Failed to load menu background! Error: " << IMG_GetError() << std::endl;
    }
}


// 🔹 Kiểm tra chuột click vào nút Start
bool isInsideButton(int x, int y) {
    return (x >= startButton.x && x <= startButton.x + startButton.w &&
        y >= startButton.y && y <= startButton.y + startButton.h);
}

// 🔹 Hiển thị menu trong cửa sổ chung
void showMenu() {
    // 🔹 Đặt cửa sổ menu thành 800x800
    SDL_SetWindowSize(window, 800, 800);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    loadMenuAssets();

    bool inMenu = true;
    SDL_Event e;

    while (inMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (isInsideButton(e.button.x, e.button.y)) {
                    gameRunning = true;
                    inMenu = false; // Thoát menu để vào game
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 🔹 Vẽ ảnh nền (có sẵn Start, Options, Quit)
        if (menuBackground) {
            SDL_RenderCopy(renderer, menuBackground, NULL, NULL);
        }

        SDL_RenderPresent(renderer);
    }

    // 🔹 Giải phóng tài nguyên menu
    SDL_DestroyTexture(menuBackground);
}
