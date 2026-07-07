#include "tile.h"
#include <string.h>

static int Board_Index(HexCoord hex) {
    int col = hex.q + BOARD_RADIUS;
    int row = hex.r + BOARD_RADIUS;
    int width = 2 * BOARD_RADIUS + 1;
    return row * width + col;
}

bool Board_InBounds(HexCoord hex) {
    return CubeDistance(hex, (HexCoord){0,0}) <= BOARD_RADIUS;
}

Tile *Board_Get(Board *board, HexCoord hex) {
    if (!Board_InBounds(hex)) return NULL;
    return &board->tiles[Board_Index(hex)];
}

void Board_Init(Board *board) {
    memset(board->tiles,0,sizeof(board->tiles));
}