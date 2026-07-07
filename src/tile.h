#ifndef TILE_H
#define TILE_H

#include "hex_grid.h"
#include <stdbool.h>

#define BOARD_RADIUS 4

typedef enum {
    TILE_EMPTY,
    TILE_ROUTE_STRAIGHT,
    TILE_ROUTE_TURN,
    TILE_ROUTE_SPLIT,
    TILE_ROUTE_INSTRUMENT
} TypeTyle;

typedef enum {
    WAVE_NONE,
    WAVE_SINE,
    WAVE_SAW,
    WAVE_SQUARE,
    WAVE_TRIANGLE
} WaveType;

typedef struct {
    TypeTyle type;
    int rotation;
    WaveType wave;
} Tile;

typedef struct {
    Tile tiles[(2*BOARD_RADIUS+1)*(2*BOARD_RADIUS+1)];
} Board;

bool Board_InBounds(HexCoord hex);
Tile *Board_Get(Board *board, HexCoord hex);
void Board_Init(Board *Board);

#endif