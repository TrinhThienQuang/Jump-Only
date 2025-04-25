#include "player.h"
#include "level.h"
#include <vector>
#include "diamond.h"
#include "pause.h"
#include "game.h"

Player player;
SDL_Texture* playerTexture = nullptr;
int playerWidth, playerHeight;
std::vector<GhostTrail> ghostTrails;
SDL_Texture* explosionTexture = nullptr;
std::vector<Explosion> explosions;


void handleInput(SDL_Event& event) {
    if (isGameOver) return;

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
            player.dy = JUMP_FORCE;
            player.dx = -MOVE_SPEED;
            if (isSound) {
                Mix_PlayChannel(-1, moveSound, 0);
            }
            else {
                Mix_HaltChannel(-1);
            }
        }
        else if (event.key.keysym.sym == SDLK_RIGHT) {
            player.dy = JUMP_FORCE;
            player.dx = MOVE_SPEED;
            if (isSound) {
                Mix_PlayChannel(-1, moveSound, 0);
            }
            else {
                Mix_HaltChannel(-1);
            }
        }
    }
}


// Thêm vụ nổ vào danh sách
void addExplosion(float x, float y) {
    explosions.emplace_back(x, y);
}

// Cập nhật vụ nổ
void updateExplosions() {
    for (auto& explosion : explosions) {
        if (explosion.active) {
            explosion.currentFrame++;
            if (explosion.currentFrame >= EXPLOSION_TOTAL_FRAMES) {
                explosion.active = false;
            }
        }
    }
    // Xóa vụ nổ 
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
        [](const Explosion& e) { return !e.active; }), explosions.end());
}


// Vẽ vụ nổ
void renderExplosions() {
    for (const auto& explosion : explosions) {
        if (explosion.active) {
            SDL_Rect srcRect = {
                (explosion.currentFrame % 5) * EXPLOSION_FRAME_WIDTH,
                (explosion.currentFrame / 5) * EXPLOSION_FRAME_HEIGHT,
                EXPLOSION_FRAME_WIDTH, EXPLOSION_FRAME_HEIGHT
            };
            SDL_Rect dstRect = {
                (int)explosion.x,
                (int)explosion.y - cameraY,
                EXPLOSION_FRAME_WIDTH, EXPLOSION_FRAME_HEIGHT
            };

            SDL_RenderCopy(renderer, explosionTexture, &srcRect, &dstRect);
        }
    }
}


void updatePlayer() {
    if (isLevelComplete) {
        return;  // Ngăn không cập nhật vị trí nhân vật khi đã hoàn thành màn chơi
    }
    player.dy += GRAVITY;
    player.y += player.dy;
    player.x += player.dx;

    if (player.x < 0) {
        player.x = 0;
        player.dx = MOVE_SPEED;
    }

    if (player.x + PLAYER_WIDTH > SCREEN_WIDTH) {
        player.x = SCREEN_WIDTH - PLAYER_WIDTH;
        player.dx = -MOVE_SPEED;
    }

    int bottomScreenY = cameraY + SCREEN_HEIGHT;
    if (player.y + PLAYER_HEIGHT >= bottomScreenY - 1) {
        player.y = bottomScreenY - PLAYER_HEIGHT;
        player.dy = JUMP_FORCE;
    }

    if (player.y < cameraY + SCREEN_HEIGHT / 2) {
        cameraY = player.y - SCREEN_HEIGHT / 2;
        if (cameraY < 0) cameraY = 0;
    }

    // Kiểm tra va chạm với kim cương
    SDL_Rect playerRect = { static_cast<int>(player.x), static_cast<int>(player.y), PLAYER_WIDTH, PLAYER_HEIGHT };
    checkDiamondCollision(playerRect);

    if (player.dy != 0) {
        ghostTrails.push_back(GhostTrail{ (int)player.x, (int)player.y, 180 });
    }

    for (auto& ghost : ghostTrails) {
        ghost.alpha -= 15;
    }

    const int MAX_TRAILS = 3;
    if (ghostTrails.size() > MAX_TRAILS) {
        ghostTrails.erase(ghostTrails.begin());
    }

    ghostTrails.erase(std::remove_if(ghostTrails.begin(), ghostTrails.end(),
        [](const GhostTrail& g) { return g.alpha <= 0; }), ghostTrails.end());

    // Thêm cập nhật vụ nổ
    updateExplosions();
}

void renderPlayer() {
    for (const auto& ghost : ghostTrails) {
        SDL_SetTextureAlphaMod(playerTexture, ghost.alpha);
        SDL_Rect ghostRect = { ghost.x, ghost.y - cameraY, PLAYER_WIDTH, PLAYER_HEIGHT };
        SDL_RenderCopy(renderer, playerTexture, NULL, &ghostRect);
    }
    SDL_SetTextureAlphaMod(playerTexture, 255);
    SDL_Rect playerRect = { player.x, player.y - cameraY, PLAYER_WIDTH, PLAYER_HEIGHT };
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
    renderExplosions();
}

