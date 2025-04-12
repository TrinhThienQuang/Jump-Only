#include "game.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    if (!init()) return -1;

    showMenu();
    if (gameRunning) {
        SDL_SetWindowSize(window, 1400, 800);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        gameLoop();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
