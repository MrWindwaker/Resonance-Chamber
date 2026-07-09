#include "tile.h"
#include <string.h>
#include <stdlib.h>

static int Board_Index(HexCoord hex) {
    int col = hex.q + BOARD_RADIUS;
    int row = hex.r + BOARD_RADIUS;
    int width = 2 * BOARD_RADIUS + 1;
    return row * width + col;
}

static int RotateEdge(int entryDir, int rotation, int offset) {
    int dirA = (0+rotation)%6;
    int dirB = (offset+rotation)%6;

    if (entryDir == dirA) return dirB;
    if (entryDir == dirB) return dirA;
    
    return -1;
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

int RouteTurn(int entryDir, int rotation) {
    return RotateEdge(entryDir, rotation, 2);
}

int RouteStraight(int entryDir, int rotation) {
    return RotateEdge(entryDir, rotation, 3);
}

bool Tile_RouteEdges(Tile tile, int *outDirA, int *outDirB) {
    int offset;

    switch (tile.type)
    {
    case TILE_ROUTE_STRAIGHT: offset = 3; break;
    case TILE_ROUTE_TURN: offset = 2; break;
    default: return false;
    }

    *outDirA = tile.rotation%6;
    *outDirB = (offset+tile.rotation)%6;

    return true;
}


Vector2 EdgeMidpoint(HexCoord hex, int dir, Vector2 origin) {
    Vector2 center = HexToScreen(hex, origin);
    Vector2 neighborCenter = HexToScreen(HexNeighbor(hex, dir), origin);

    return (Vector2) {
        (center.x + neighborCenter.x)/2.0f,
        (center.y + neighborCenter.y)/2.0f,
    };
}

void DrawTileRoute(HexCoord hex, Tile tile, Vector2 origin) {
    int dirA, dirB;
    if(!Tile_RouteEdges(tile, &dirA, &dirB)) return;

    Vector2 a = EdgeMidpoint(hex, dirA, origin);
    Vector2 b = EdgeMidpoint(hex, dirB, origin);

    DrawLineEx(a,b,4.0f, (Color){240,200,80,255});
}