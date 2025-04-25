#include "menu.h"
#include "game.h"
#include <SDL_image.h>
#include <iostream>
#include "pause.h"

bool gameRunning = false;
SDL_Rect startButton = { 290, 260, 220, 80 };
SDL_Rect quitButton = { 290, 600, 220, 80 };
SDL_Rect levelButton = { 290, 370, 220, 80 };
SDL_Rect optionsButton = { 290, 490, 220, 80 };
SDL_Texture* menuBackground = nullptr;
SDL_Texture* levelMenuBackground = nullptr;
SDL_Texture* musicOffTexture = nullptr;
SDL_Texture* musicOnTexture = nullptr;
SDL_Texture* soundOffTexture = nullptr;
SDL_Texture* optionsOffTexture = nullptr;

//  Load ảnh nền menu
void loadMenuAssets() {
    menuBackground = IMG_LoadTexture(renderer, "image/menu3.png");
    if (!menuBackground) {
        std::cout << "Failed to load menu background! Error: " << IMG_GetError() << std::endl;
    }
}

//  Load ảnh nền menu Level
void loadLevelMenuAssets() {
    levelMenuBackground = IMG_LoadTexture(renderer, "image/level.png");
    if (!levelMenuBackground) {
        std::cout << "Failed to load level menu background! Error: " << IMG_GetError() << std::endl;
    }
}

// Load ảnh nền setting
void loadOptionsMenuAssets() {
    musicOffTexture = IMG_LoadTexture(renderer, "image/musicoff.png");
    musicOnTexture = IMG_LoadTexture(renderer, "image/musicon.png"); 
    soundOffTexture = IMG_LoadTexture(renderer, "image/soundOff.png");
    optionsOffTexture = IMG_LoadTexture(renderer, "image/sound1.png");

    if (!musicOffTexture || !musicOnTexture) {
        std::cout << "Failed to load options assets! Error: " << IMG_GetError() << std::endl;
    }
}


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
    SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_RenderPresent(renderer);
}


void showMenu() {
    SDL_SetWindowSize(window, 800, 800);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    loadMenuAssets();
    gameRunning = false;
    bool inMenu = true;
    SDL_Event e;
    Mix_HaltMusic();

    if (isMusicOn && menuMusic && Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(menuMusic, -1);
    }

    while (inMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (isInsideButton(e.button.x, e.button.y)) {
                    showLevelMenu();
                    inMenu = false;
                }
                if (isQuitButton(e.button.x, e.button.y)) {
                    SDL_Quit();
                    exit(0);
                }
                if (isLevelButton(e.button.x, e.button.y)) {
                    showLevelMenu();
                    return;
                }
                if (isOptionsButton(e.button.x, e.button.y)) {
                    showOptionsMenu();
                    return;
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

    resetWindow();
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
                    restartGame();
                    Mix_HaltMusic();
                    if (isMusicOn) {
                        Mix_PlayMusic(backgroundMusic, -1);
                    }

                    resetWindow();
                    gameState = LEVEL_1;
                    setupLevel1();
                    inLevelMenu = false;
                }
                if (x >= normalButton.x && x <= normalButton.x + normalButton.w &&
                    y >= normalButton.y && y <= normalButton.y + normalButton.h) {
                    std::cout << "Normal Mode Selected! Starting game...\n";
                    restartGame();
                    Mix_HaltMusic();
                    if (isMusicOn) {
                        Mix_PlayMusic(backgroundMusic, -1);
                    }

                    gameState = LEVEL_2;
                    setupLevel2();
                    resetWindow();
                    inLevelMenu = false;
                }
                if (x >= hardButton.x && x <= hardButton.x + hardButton.w &&
                    y >= hardButton.y && y <= hardButton.y + hardButton.h) {
                    std::cout << "Hard Mode Selected! Starting game...\n";
                    restartGame();
                    Mix_HaltMusic();
                    if (isMusicOn) {
                        Mix_PlayMusic(backgroundMusic, -1);
                    }

                    gameState = LEVEL_3;
                    setupLevel3();
                    resetWindow();
                    inLevelMenu = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (levelMenuBackground) SDL_RenderCopy(renderer, levelMenuBackground, NULL, NULL);
        SDL_RenderPresent(renderer);
        if (!inLevelMenu) break;
    }
    gameRunning = true;
}



void showOptionsMenu() {
    SDL_SetWindowSize(window, 800, 800); // đặt lại cửa sổ thành 800x800
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    loadOptionsMenuAssets(); // Load ảnh nền trước khi hiển thị

    bool inOptionsMenu = true;
    SDL_Event e;
    SDL_Rect musicButton = { 140, 290, 510, 90 };
    SDL_Rect soundButton = { 140, 420, 510, 90 };
    SDL_Rect backButton = { 270, 560, 260, 80 };

    while (inOptionsMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x, y = e.button.y;
                if (x >= musicButton.x && x <= musicButton.x + musicButton.w &&
                    y >= musicButton.y && y <= musicButton.y + musicButton.h) {
                    isMusicOn = !isMusicOn; // đảo trạng thái nhạc
                    if (isMusicOn) {
                        //  Nếu đang ở menu, phát nhạc menu
                        if (!gameRunning) {
                            Mix_PlayMusic(menuMusic, -1);
                        }
                        //  Nếu đang trong game, phát nhạc game
                        else {
                            Mix_PlayMusic(backgroundMusic, -1);
                        }
                    }
                    else {
                        Mix_HaltMusic(); // Tắt nhạc ngay lập tức
                    }
                }
                else if (x >= soundButton.x && x <= soundButton.x + soundButton.w &&
                    y >= soundButton.y && y <= soundButton.y + soundButton.h) {
                    isSound = !isSound;
                }
                else if (x >= quitButton.x && x <= quitButton.x + quitButton.w &&
                    y >= quitButton.y && y <= quitButton.y + quitButton.h) {
                    inOptionsMenu = false;
                }

            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (isMusicOn && isSound && musicOnTexture) {
            SDL_RenderCopy(renderer, musicOnTexture, NULL, NULL);
        }
        else if (!isMusicOn && isSound && musicOffTexture) {
            SDL_RenderCopy(renderer, musicOffTexture, NULL, NULL);
        }
        else if (isMusicOn && !isSound && soundOffTexture) {
            SDL_RenderCopy(renderer, soundOffTexture, NULL, NULL);
        }
        else if (!isMusicOn && !isSound && optionsOffTexture) {
            SDL_RenderCopy(renderer, optionsOffTexture, NULL, NULL);
        }
        else {
            std::cout << "Options menu background not loaded!" << std::endl;
        }


        SDL_RenderPresent(renderer);
    }
    showMenu();
    SDL_DestroyTexture(musicOnTexture);
    SDL_DestroyTexture(musicOffTexture);
    musicOnTexture = nullptr;
    musicOffTexture = nullptr;

}