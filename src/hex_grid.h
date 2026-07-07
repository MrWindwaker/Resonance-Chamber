#ifndef HEX_GRID_H
#define HEX_GRID_H

#include "raylib.h"

#define HEX_SIZE 40.0f
#define ISO_SQUASH 0.6f

typedef struct {
    int q;
    int r;
} HexCoord;

extern const HexCoord HEX_DIRECTIONS[6];

int CubeDistance(HexCoord a, HexCoord b);
HexCoord HexNeighbor(HexCoord hex, int direction);
Vector2 HexToScreen(HexCoord hex, Vector2 origin);
HexCoord ScreenToHex(Vector2 point, Vector2 origin);
void HexCorners(Vector2 center, Vector2 outCorners[6]);

void DrawHex(HexCoord hex, Vector2 origin, Color fillColor, Color lineColor);

#endif