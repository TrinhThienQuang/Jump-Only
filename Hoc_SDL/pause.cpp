#include "pause.h"
#include <SDL_image.h>
#include "game.h"
#include "menu.h"

bool isPaused = false;
SDL_Texture* pauseScreenTexture = nullptr;
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

        SDL_Rect playButton = { 610, 270, 180, 70 };
        SDL_Rect restartButton = { 610, 370, 180, 40 };
        SDL_Rect optionsButton = { 610, 400, 180, 70 }; 
        SDL_Rect quitButton = { 610, 500, 180, 40 };

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
            // Xử lý mở menu tùy chọn nếu cần
        }
        else if (mouseX >= quitButton.x && mouseX <= quitButton.x + quitButton.w &&
            mouseY >= quitButton.y && mouseY <= quitButton.y + quitButton.h) {
            showMenu(); // Vào lại menu
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


void renderPauseScreen() {
    if (isPaused) {
        // Hiển thị texture khung hình trước
        if (previousFrameTexture) {
            SDL_RenderCopy(renderer, previousFrameTexture, NULL, NULL);
        }

        // Tạo lớp phủ làm tối màn hình
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Bật chế độ blend
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100); // Màu đen với độ trong suốt
        SDL_Rect overlay = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &overlay);

        // Hiển thị ảnh Pause ở giữa màn hình
        SDL_Surface* pauseSurface = IMG_Load("pause1.png");
        if (pauseSurface) {
            SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);

            int pauseW = 360; // Chiều rộng ảnh Pause
            int pauseH = 460; // Chiều cao ảnh Pause

            SDL_Rect pauseRect = {
                (SCREEN_WIDTH - pauseW) / 2,
                (SCREEN_HEIGHT - pauseH) / 2,
                pauseW,
                pauseH
            };

            SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
            SDL_DestroyTexture(pauseTexture);
            SDL_FreeSurface(pauseSurface);
        }
    }
}


