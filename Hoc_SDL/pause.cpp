#include "pause.h"
#include <SDL_image.h>
#include "game.h"
#include "menu.h"
#include "diamond.h"

bool isPaused = false;
bool isOptionsScreen = false; 
bool isGameOver = false;
bool isLevelComplete = false;
bool isMusicOn = true; 
bool isSound = true;
SDL_Texture* previousFrameTexture = nullptr;

void handlePauseEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        isPaused = !isPaused;
        if (isPaused) {
            Mix_PauseMusic();  // dừng nhạc khi pause
        }
        else {
            Mix_ResumeMusic();
        }
    }
    if (isPaused && !isOptionsScreen && event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect playButton = { 530, 350, 150, 100 };
        SDL_Rect restartButton = { 720, 350, 150, 100 };
        SDL_Rect optionsButton = { 530, 490, 150, 100 };
        SDL_Rect quitButton = { 720, 490, 100, 100 };

        if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
            mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
            Mix_ResumeMusic();
            isPaused = false;
        }
        else if (mouseX >= restartButton.x && mouseX <= restartButton.x + restartButton.w &&
            mouseY >= restartButton.y && mouseY <= restartButton.y + restartButton.h) {
            restartGame(); 
        }
        else if (mouseX >= optionsButton.x && mouseX <= optionsButton.x + optionsButton.w &&
            mouseY >= optionsButton.y && mouseY <= optionsButton.y + optionsButton.h) {
            isOptionsScreen = true;  
        }
        else if (mouseX >= quitButton.x && mouseX <= quitButton.x + quitButton.w &&
            mouseY >= quitButton.y && mouseY <= quitButton.y + quitButton.h) {
            restartGame();
            showMenu();
        }
    }

    if (isOptionsScreen && event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_Rect musicButton = { 610, 315, 160, 65 };  // Nút Music
        SDL_Rect soundButton = { 610, 405, 160, 65 };  // Nút Sound
        SDL_Rect backButton = { 610, 495, 160, 65 };  // Nút Back
        SDL_Rect backButton1 = { 815, 250, 30, 30 };  // Nút Back

        if (mouseX >= musicButton.x && mouseX <= musicButton.x + musicButton.w &&
            mouseY >= musicButton.y && mouseY <= musicButton.y + musicButton.h) {
            isMusicOn = !isMusicOn;
            if (isMusicOn) {
                if (!gameRunning) {
                    Mix_PlayMusic(menuMusic, -1);
                }
                else {
                    Mix_PlayMusic(backgroundMusic, -1);
                }
            }
            else {
                Mix_HaltMusic();
            }
        }
        else if (mouseX >= soundButton.x && mouseX <= soundButton.x + soundButton.w &&
            mouseY >= soundButton.y && mouseY <= soundButton.y + soundButton.h) {
            isSound = !isSound;
        }
        else if ((mouseX >= backButton.x && mouseX <= backButton.x + backButton.w &&
            mouseY >= backButton.y && mouseY <= backButton.y + backButton.h) ||
            (mouseX >= backButton1.x && mouseX <= backButton1.x + backButton1.w &&
                mouseY >= backButton1.y && mouseY <= backButton1.y + backButton1.h)) {
            isOptionsScreen = false;  // Quay lại màn hình Pause
        }
    }

    if (isGameOver && event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Rect retryButton = { 590, 330, 230, 120 }; // Nút chơi lại
        SDL_Rect exitButton = { 590, 480, 230, 120 };    // Nút về menu

        if (mouseX >= retryButton.x && mouseX <= retryButton.x + retryButton.w &&
            mouseY >= retryButton.y && mouseY <= retryButton.y + retryButton.h) {
            isGameOver = false;
            restartGame();
        }
        else if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.w &&
            mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.h) {
            isGameOver = false;
            showMenu();
        }
    }
    if (isLevelComplete && event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_Rect replayButton = { 580, 470, 235, 40 }; // nút Replay
        SDL_Rect menuButton = { 580, 530, 235, 70 };   // nút Menu
        if (mouseX >= replayButton.x && mouseX <= replayButton.x + replayButton.w &&
            mouseY >= replayButton.y && mouseY <= replayButton.y + replayButton.h) {
            isLevelComplete = false;
            restartGame();
        }
        else if (mouseX >= menuButton.x && mouseX <= menuButton.x + menuButton.w &&
            mouseY >= menuButton.y && mouseY <= menuButton.y + menuButton.h) {
            isLevelComplete = false;
            showMenu();
        }
    }
}


void captureCurrentFrame() {
    if (previousFrameTexture) {
        SDL_DestroyTexture(previousFrameTexture);
    }
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);
    previousFrameTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}


void renderGameOverScreen() {
    if (isGameOver) {
        Mix_HaltMusic();
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Surface* gameOverSurface = IMG_Load("image/gameover.png");
        if (gameOverSurface) {
            SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
            SDL_Rect gameOverRect = { (SCREEN_WIDTH - 500) / 2, (SCREEN_HEIGHT - 500) / 2, 500, 500 };
            SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
            SDL_DestroyTexture(gameOverTexture);
            SDL_FreeSurface(gameOverSurface);
        }
    }
}



void renderPauseScreen() {
    if (isPaused && !isOptionsScreen) {
        if (previousFrameTexture) {
            SDL_RenderCopy(renderer, previousFrameTexture, NULL, NULL);
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Surface* pauseSurface = IMG_Load("image/pause3.png");
        if (pauseSurface) {
            SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
            SDL_Rect pauseRect = { (SCREEN_WIDTH - 500) / 2, (SCREEN_HEIGHT - 500) / 2, 500, 500 };
            SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
            SDL_DestroyTexture(pauseTexture);
            SDL_FreeSurface(pauseSurface);
        }
    }
}


void renderOptionsScreen() {
    if (isOptionsScreen) {
        if (previousFrameTexture) {
            SDL_RenderCopy(renderer, previousFrameTexture, NULL, NULL);
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Surface* optionsSurface = IMG_Load("image/option4.png");
        if (optionsSurface) {
            SDL_Texture* optionsTexture = SDL_CreateTextureFromSurface(renderer, optionsSurface);
            SDL_Rect optionsRect = { (SCREEN_WIDTH - 500) / 2, (SCREEN_HEIGHT - 500) / 2, 500, 500 };
            SDL_RenderCopy(renderer, optionsTexture, NULL, &optionsRect);
            SDL_DestroyTexture(optionsTexture);
            SDL_FreeSurface(optionsSurface);
        }
    }
}


void renderLevelCompleteScreen() {
    if (isLevelComplete) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);
        const char* starImage = "image/stars_0.png";
        if (collectedDiamonds == 1) {
            starImage = "image/star1.png";
        }
        else if (collectedDiamonds == 2) {
            starImage = "image/star2.png";
        }
        else if (collectedDiamonds == 3) {
            starImage = "image/star3.png";
        }
        else if (collectedDiamonds == 0) {
            starImage = "image/star0.png";
        }

        // Tải ảnh sao tương ứng
        SDL_Surface* starSurface = IMG_Load(starImage);
        if (starSurface) {
            SDL_Texture* starTexture = SDL_CreateTextureFromSurface(renderer, starSurface);
            SDL_Rect starRect = { (SCREEN_WIDTH - 500) / 2, (SCREEN_HEIGHT - 500) / 2, 500, 500 };
            SDL_RenderCopy(renderer, starTexture, NULL, &starRect);
            SDL_DestroyTexture(starTexture);
            SDL_FreeSurface(starSurface);
        }
    }
}


