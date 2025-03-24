#include "player.h"

Player player;
SDL_Texture* playerTexture = nullptr;
int playerWidth, playerHeight;

void renderPlayer() {
    SDL_Rect playerRect = { player.x, player.y - cameraY, PLAYER_WIDTH, PLAYER_HEIGHT };
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
}

void updatePlayer() {
    // Áp dụng trọng lực
    player.dy += GRAVITY;
    player.y += player.dy;
    player.x += player.dx;

    // Xử lý va chạm với biên màn hình
    if (player.x < 0) {
        player.x = 0;
        player.dx = MOVE_SPEED; // Bật lại khi chạm cạnh trái
    }
    if (player.x + PLAYER_WIDTH > SCREEN_WIDTH) {
        player.x = SCREEN_WIDTH - PLAYER_WIDTH;
        player.dx = -MOVE_SPEED; // Bật lại khi chạm cạnh phải
    }

    // Tính đáy màn hình theo camera
    int bottomScreenY = cameraY + SCREEN_HEIGHT;

    // Chỉ xét va chạm đáy khi nhân vật thực sự chạm đáy, tránh lỗi game over ngay
    if (player.y + PLAYER_HEIGHT >= bottomScreenY - 1) {  
        player.y = bottomScreenY - PLAYER_HEIGHT;
        player.dy = JUMP_FORCE; // Bật lên khi chạm đáy
    }

    // Cập nhật camera
    if (player.y < cameraY + SCREEN_HEIGHT / 2) {
        cameraY = player.y - SCREEN_HEIGHT / 2;
        if (cameraY < 0) cameraY = 0;
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
