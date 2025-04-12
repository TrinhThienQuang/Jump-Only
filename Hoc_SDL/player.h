#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "game.h"
#include <vector>

struct Player {
    float x, y;
    float dx, dy;
};

struct GhostTrail {
    int x, y;
    int alpha;
};

struct Explosion {
    float x, y;
    int currentFrame = 0;
    int frameDelay = 5;    // Độ trễ giữa các frame
    bool active;

    Explosion(float _x, float _y) : x(_x), y(_y), currentFrame(0), active(true) {}
};

extern Player player;
extern SDL_Texture* playerTexture;
extern int playerWidth, playerHeight;
extern SDL_Texture* spikeTexture;
extern SDL_Texture* explosionTexture;
extern std::vector<Explosion> explosions;


const float JUMP_FORCE = -12.0f;        // Lực nhảy
const float GRAVITY = 0.7f;             // lực rơi xuống
const float MOVE_SPEED = 5.0f;          // tốc độ di chuyển
const int PLAYER_WIDTH = 50;            // chiều rộng nhân vật
const int PLAYER_HEIGHT = 50;           // chiều cao nhân vật
const int EXPLOSION_TOTAL_FRAMES = 10;  // Số frame trong hiệu ứng nổ
const int EXPLOSION_FRAME_WIDTH = 158;  // Chiều rộng 1 frame nổ
const int EXPLOSION_FRAME_HEIGHT = 158; // Chiều cao 1 frame nổ


void renderPlayer();
void updatePlayer();
void handleInput(SDL_Event& event);
void addExplosion(float x, float y);
void updateExplosions();
void renderExplosions();

#endif
