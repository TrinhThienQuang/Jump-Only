#ifndef PAUSE_H
#define PAUSE_H

#include <SDL.h>

extern bool isPaused;
extern bool isOptionsScreen;

void handlePauseEvent(SDL_Event& event);
void renderPauseScreen();
void captureCurrentFrame();
void renderOptionsScreen();

#endif
