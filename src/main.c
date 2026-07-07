#include "raylib.h"
#include <math.h>
#include <stdlib.h>

#include "hex_grid.h"
#include "tile.h"

#define SCREEN_SIZE 720

int main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Resonance Chamber - hex grid test");
    SetTargetFPS(60);
    SetExitKey(0);

    Vector2 origin = { SCREEN_SIZE / 2.0f, SCREEN_SIZE / 2.0f };
    Board board;
    Board_Init(&board);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        HexCoord hovered = ScreenToHex(mouse, origin);
        bool hoveredInBoard = Board_InBounds(hovered);

        BeginDrawing();
        ClearBackground((Color){ 20, 20, 28, 255 });

        for (int q = -BOARD_RADIUS; q <= BOARD_RADIUS; q++)
        {
            int r1 = -BOARD_RADIUS > -q - BOARD_RADIUS ? -BOARD_RADIUS : -q - BOARD_RADIUS;
            int r2 =  BOARD_RADIUS <  -q + BOARD_RADIUS ?  BOARD_RADIUS : -q + BOARD_RADIUS;

            for (int r = r1; r <= r2; r++)
            {
                HexCoord hex = { q, r };
                bool isHovered = hoveredInBoard && hex.q == hovered.q && hex.r == hovered.r;

                Color fill = isHovered ? (Color){ 80, 140, 200, 255 } : (Color){ 40, 44, 58, 255 };
                Color line = (Color){ 90, 100, 120, 255 };

                DrawHex(hex, origin, fill, line);
            }
        }

        DrawText(TextFormat("hex: %d, %d", hovered.q, hovered.r), 10, 10, 20, RAYWHITE);
        DrawFPS(SCREEN_SIZE - 90, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}