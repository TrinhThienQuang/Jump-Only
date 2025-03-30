#ifndef PAUSE_H
#define PAUSE_H

#include <SDL.h>

extern bool isPaused;
extern bool isGameOver;
extern bool isOptionsScreen;
extern bool isLevelComplete;
extern bool isMusicOn;


void handlePauseEvent(SDL_Event& event);
void renderPauseScreen();
void captureCurrentFrame();
void renderOptionsScreen();
void renderGameOverScreen();
void renderLevelCompleteScreen();

#endif
