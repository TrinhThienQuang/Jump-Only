#include "pause.h"
#include <SDL_image.h>
#include "game.h"
#include "menu.h"

bool isPaused = false;
bool isOptionsScreen = false;  // Biến xác định có đang ở màn hình options không
SDL_Texture* previousFrameTextureGameOver = nullptr; // Lưu khung hình trước khi game over
bool isGameOver = false;


SDL_Texture* previousFrameTexture = nullptr;

void handlePauseEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        isPaused = !isPaused;
        if (isPaused) {
            captureCurrentFrame(); // Chụp khung hình hiện tại
        }
    }
    if (isPaused && event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_Rect playButton = { 530, 350, 150, 100 };
        SDL_Rect restartButton = { 720, 350, 150, 100 };
        SDL_Rect optionsButton = { 530, 490, 150, 100 }; 
        SDL_Rect quitButton = { 720, 490, 100, 100 };

        if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
            mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
            isPaused = false; // Tiếp tục chơi
        }
        else if (mouseX >= restartButton.x && mouseX <= restartButton.x + restartButton.w &&
            mouseY >= restartButton.y && mouseY <= restartButton.y + restartButton.h) {
            restartGame(); // Gọi hàm restart game
        }
        else if (mouseX >= optionsButton.x && mouseX <= optionsButton.x + optionsButton.w &&
            mouseY >= optionsButton.y && mouseY <= optionsButton.y + optionsButton.h) {
            isOptionsScreen = true;  // Chuyển sang màn hình options
        }
        else if (isOptionsScreen) {
            // Tọa độ các nút trong Options menu
            SDL_Rect musicButton = { 610, 315, 160, 65 };  // Nút Music
            SDL_Rect soundButton = { 610, 405, 160, 65 };  // Nút Sound
            SDL_Rect backButton = { 610, 495, 160, 65 };  // Nút Back
            SDL_Rect backButton1 = { 815, 250, 30, 30 };  // Nút Back
            std::cout << mouseX << ' ' << mouseY << std::endl;
            // Nhấn vào nút Music (tạm thời chưa xử lý logic)
            if (mouseX >= musicButton.x && mouseX <= musicButton.x + musicButton.w &&
                mouseY >= musicButton.y && mouseY <= musicButton.y + musicButton.h) {
                // TODO: Tắt / bật nhạc nền
            }
            // Nhấn vào nút Sound (tạm thời chưa xử lý logic)
            else if (mouseX >= soundButton.x && mouseX <= soundButton.x + soundButton.w &&
                mouseY >= soundButton.y && mouseY <= soundButton.y + soundButton.h) {
                // TODO: Tắt / bật âm thanh
            }
            // Nhấn vào nút Back để quay lại Pause
            else if (mouseX >= backButton.x && mouseX <= backButton.x + backButton.w &&
                mouseY >= backButton.y && mouseY <= backButton.y + backButton.h) {
                isOptionsScreen = false;  // Quay lại màn hình Pause
                isPaused = true;           // Đảm bảo màn hình Pause vẫn hiển thị
            }
            else if (mouseX >= backButton1.x && mouseX <= backButton1.x + backButton1.w &&
                mouseY >= backButton1.y && mouseY <= backButton1.y + backButton1.h) {
                isOptionsScreen = false;  // Quay lại màn hình Pause
                isPaused = true;           // Đảm bảo màn hình Pause vẫn hiển thị
            }
        }

        else if (mouseX >= quitButton.x && mouseX <= quitButton.x + quitButton.w &&
            mouseY >= quitButton.y && mouseY <= quitButton.y + quitButton.h) {
            restartGame();
            showMenu(); // Vào lại menu
        }
    }
    if (isGameOver && event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        std::cout << mouseX << ' ' << mouseY << std::endl;
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

}



void captureCurrentFrame() {
    if (previousFrameTexture) {
        SDL_DestroyTexture(previousFrameTexture);
    }

    // Tạo một surface để lưu hình ảnh từ renderer
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA8888);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, surface->pixels, surface->pitch);

    // Chuyển surface thành texture
    previousFrameTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface); // Giải phóng surface sau khi sử dụng
}


void renderGameOverScreen() {
    if (isGameOver) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Surface* gameOverSurface = IMG_Load("gameover.png");
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
    if (isPaused && !isOptionsScreen) {  // Chỉ vẽ màn hình pause nếu không ở options
        if (previousFrameTexture) {
            SDL_RenderCopy(renderer, previousFrameTexture, NULL, NULL);
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);

        SDL_Surface* pauseSurface = IMG_Load("pause3.png");
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

        SDL_Surface* optionsSurface = IMG_Load("option4.png");
        if (optionsSurface) {
            SDL_Texture* optionsTexture = SDL_CreateTextureFromSurface(renderer, optionsSurface);
            SDL_Rect optionsRect = { (SCREEN_WIDTH - 500) / 2, (SCREEN_HEIGHT - 500) / 2, 500, 500 };
            SDL_RenderCopy(renderer, optionsTexture, NULL, &optionsRect);
            SDL_DestroyTexture(optionsTexture);
            SDL_FreeSurface(optionsSurface);
        }
    }
}



