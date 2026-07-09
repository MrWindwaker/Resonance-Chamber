#include "hex_grid.h"
#include <math.h>
#include <stdlib.h>

const HexCoord HEX_DIRECTIONS[6] = {
    {1,0}, {1,-1},{0,-1},
    {-1,0}, {-1,1},{0,1}
};

int CubeDistance(HexCoord a, HexCoord b)
{
    int aq = a.q, ar = a.r, as = -a.q - a.r;
    int bq = b.q, br = b.r, bs = -b.q - b.r;
    int dq = abs(aq - bq);
    int dr = abs(ar - br);
    int ds = abs(as - bs);
    int m = dq > dr ? dq : dr;
    return m > ds ? m : ds;
}

Vector2 HexToScreen(HexCoord hex, Vector2 origin)
{
    float x = HEX_SIZE * (sqrtf(3.0f) * hex.q + sqrtf(3.0f) / 2.0f * hex.r);
    float y = HEX_SIZE * (3.0f / 2.0f * hex.r);

    y *= ISO_SQUASH;

    return (Vector2){ origin.x + x, origin.y + y };
}

HexCoord ScreenToHex(Vector2 point, Vector2 origin)
{
    float x = (point.x - origin.x);
    float y = (point.y - origin.y) / ISO_SQUASH;

    float q = (sqrtf(3.0f) / 3.0f * x - 1.0f / 3.0f * y) / HEX_SIZE;
    float r = (2.0f / 3.0f * y) / HEX_SIZE;

    // cube rounding
    float cx = q;
    float cz = r;
    float cy = -cx - cz;

    float rx = roundf(cx);
    float ry = roundf(cy);
    float rz = roundf(cz);

    float xDiff = fabsf(rx - cx);
    float yDiff = fabsf(ry - cy);
    float zDiff = fabsf(rz - cz);

    if (xDiff > yDiff && xDiff > zDiff)
        rx = -ry - rz;
    else if (yDiff > zDiff)
        ry = -rx - rz;
    else
        rz = -rx - ry;

    return (HexCoord){ (int)rx, (int)rz };
}

void DrawHex(HexCoord hex, Vector2 origin, Color fillColor, Color lineColor)
{
    Vector2 center = HexToScreen(hex, origin);
    Vector2 corners[6];
    HexCorners(center, corners);

    for (int i = 0; i < 6; i++)
    {
        Vector2 a = corners[i];
        Vector2 b = corners[(i + 1) % 6];
        DrawTriangle(center, b, a, fillColor);
    }

    for (int i = 0; i < 6; i++)
    {
        Vector2 a = corners[i];
        Vector2 b = corners[(i + 1) % 6];
        DrawLineEx(a, b, 2.0f, lineColor);
    }
}

HexCoord HexNeighbor(HexCoord hex, int direction) {
    HexCoord d = HEX_DIRECTIONS[direction];
    return (HexCoord){hex.q+d.q, hex.r+d.r};
}

void HexCorners(Vector2 center, Vector2 outCorners[6]) {
    for (int i = 0; i < 6; i++)
    {
        float angle = (60.0f * i + 30.0f) * DEG2RAD; 
        float dx = HEX_SIZE * cosf(angle);
        float dy = HEX_SIZE * sinf(angle) * ISO_SQUASH;
        outCorners[i] = (Vector2){ center.x + dx, center.y + dy };
    }
}


Vector2 HexEdgeMidpoint(HexCoord hex, int direction, Vector2 origin) {
    Vector2 a = HexToScreen(hex, origin);
    Vector2 b = HexToScreen(HexNeighbor(hex, direction),origin);

    return (Vector2){(a.x+b.x)/2.0f, (a.y+b.y)/2.0};
}