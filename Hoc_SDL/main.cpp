#include "game.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    if (!init()) return -1;

    showMenu();  // Chạy menu trước

    // Khi menu kết thúc, đổi kích thước cửa sổ sang 1400x800 rồi chạy game
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
