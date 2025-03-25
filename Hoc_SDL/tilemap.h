#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL.h>
#include "game.h"

const int TILE_SIZE = 50; // Kích thước mỗi ô vuông
const int MAP_WIDTH = 16; // Số ô theo chiều ngang
const int MAP_HEIGHT = 50; // Số ô theo chiều dọc (LEVEL_HEIGHT / TILE_SIZE)

// Khai báo mảng tileMap
extern const int tileMap[MAP_HEIGHT][MAP_WIDTH];


#endif