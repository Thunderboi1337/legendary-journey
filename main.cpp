#include <iostream>
#include <raylib.h>

#define FPS 60

Texture2D carl;

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Main window");
    SetTargetFPS(FPS);
    SetWindowPosition(100, 100);
    carl = LoadTexture("carl.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(carl, 0, 0, WHITE);

        EndDrawing();
    }

    UnloadTexture(carl);
    CloseWindow();

    return 0;
}