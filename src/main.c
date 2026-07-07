#include "raylib.h"

int main(void) {
    InitWindow(720, 720, "hex merge test");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Hello, web web!", 260, 340, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}