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

    bool rotate = false;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        HexCoord hovered = ScreenToHex(mouse, origin);
        bool hoveredInBoard = Board_InBounds(hovered);

        if (hoveredInBoard && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !rotate) {
            Tile *center = Board_Get(&board, hovered);
            if (!center->type) {
                center->type = TILE_ROUTE_STRAIGHT;
                center->rotation = 0;
            }
        }

        if (IsKeyPressed(KEY_R)) {
            rotate = !rotate;
        }

        if (rotate && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Tile *tile = Board_Get(&board, hovered);
            if (tile->type) {
                tile->rotation = (tile->rotation+1)%6;
            }
        }

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

                Tile *tile = Board_Get(&board, hex);
                if(tile) DrawTileRoute(hex, *tile, origin);
            }
        }

        DrawText(TextFormat("hex: %d, %d", hovered.q, hovered.r), 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Rotate: %b", rotate, hovered.r), 10, 30, 20, RAYWHITE);
        DrawFPS(SCREEN_SIZE - 90, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}