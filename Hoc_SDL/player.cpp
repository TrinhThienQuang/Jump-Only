#include "player.h"
#include "level.h"
#include <vector>


Player player;
SDL_Texture* playerTexture = nullptr;
int playerWidth, playerHeight;
std::vector<GhostTrail> ghostTrails;



bool checkTileCollision(int x, int y) {
    int tileX = x / TILE_SIZE;
    int tileY = y / TILE_SIZE;

    // Kiểm tra nếu ngoài phạm vi map hoặc chạm vào tile 1 (tường)
    if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
        return true;
    }
    return false;
}

void renderPlayer() {
    // Vẽ dư ảnh trước nhân vật
    for (const auto& ghost : ghostTrails) {
        SDL_SetTextureAlphaMod(playerTexture, ghost.alpha); // Đặt độ trong suốt
        SDL_Rect ghostRect = { ghost.x, ghost.y - cameraY, PLAYER_WIDTH, PLAYER_HEIGHT };
        SDL_RenderCopy(renderer, playerTexture, NULL, &ghostRect);
    }

    // Reset alpha về bình thường trước khi vẽ nhân vật
    SDL_SetTextureAlphaMod(playerTexture, 255);

    // Vẽ nhân vật chính
    SDL_Rect playerRect = { player.x, player.y - cameraY, PLAYER_WIDTH, PLAYER_HEIGHT };
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
}





void updatePlayer() {
    // Áp dụng trọng lực
    player.dy += GRAVITY;
    player.y += player.dy;
    player.x += player.dx;

    // Xử lý va chạm với biên trái
    if (player.x < 0) {
        player.x = 0;
        player.dx = MOVE_SPEED; // Bật lại khi chạm cạnh trái
    }

    // Xử lý va chạm với biên phải
    if (player.x + PLAYER_WIDTH > SCREEN_WIDTH) {
        player.x = SCREEN_WIDTH - PLAYER_WIDTH;
        player.dx = -MOVE_SPEED; // Bật lại khi chạm cạnh phải
    }

    // Xử lý va chạm đáy màn hình
    int bottomScreenY = cameraY + SCREEN_HEIGHT;
    if (player.y + PLAYER_HEIGHT >= bottomScreenY - 1) {
        player.y = bottomScreenY - PLAYER_HEIGHT;
        player.dy = JUMP_FORCE;

    }

    // Cập nhật camera theo nhân vật
    if (player.y < cameraY + SCREEN_HEIGHT / 2) {
        cameraY = player.y - SCREEN_HEIGHT / 2;
        if (cameraY < 0) cameraY = 0; // Không cho camera vượt khỏi viền trên
    }

    // dư ảnh
    if (player.dy != 0) {
        ghostTrails.push_back(GhostTrail{ (int)player.x, (int)player.y, 180 }); // Alpha ban đầu là 180
    }

    // Giảm độ trong suốt của dư ảnh và xóa nếu quá mờ
    for (auto& ghost : ghostTrails) {
        ghost.alpha -= 15; // Mờ dần
    }
    const int MAX_TRAILS = 3; // Chỉ lưu tối đa 5 dư ảnh
    if (ghostTrails.size() > MAX_TRAILS) {
        ghostTrails.erase(ghostTrails.begin()); // Xóa dư ảnh cũ nhất
    }

    ghostTrails.erase(std::remove_if(ghostTrails.begin(), ghostTrails.end(),
        [](const GhostTrail& g) { return g.alpha <= 0; }), ghostTrails.end());

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
