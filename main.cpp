#include <iostream>
#include <raylib.h>
#include <vector>
#include "guy.h"

#define FPS 60

const int screenWidth = 800;
const int screenHeight = 450;

Texture2D carl;

Guy guy = Guy();

void init(void)
{
    InitWindow(screenWidth, screenHeight, "Main window");
    SetTargetFPS(FPS);
    carl = LoadTexture("carl.png");
}

void exit(void)
{
    UnloadTexture(carl);
    CloseWindow();
}

void input(void)
{
    guy.input();
}

void update(void)
{
    guy.cooldowns(0.2);
}

void render(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    guy.update();
    EndDrawing();
}

int main(void)
{
    init();

    while (!WindowShouldClose())
    {
        input();
        update();
        render();
    }

    exit();

    return 0;
}
