#include <iostream>
#include <raylib.h>
#include <vector>
#include "guy.h"
#include "grid.h"
#include "objects.h"

#define FPS 60

const int screenWidth = 800;
const int screenHeight = 450;

void init(void)
{
    InitWindow(screenWidth, screenHeight, "Main window");
    SetTargetFPS(FPS);
}

int main(void)
{
    init();
    Guy guy = Guy();
    Grid grid = Grid();
    Objects objects = Objects();

    Camera2D cam = {0};
    cam.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    objects.GetWorldObjects();

    while (!WindowShouldClose())
    {
        guy.input(objects.GetObjects());
        bool isColliding = objects.isColliding(guy.GetRect());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(cam);

        grid.render();
        objects.render();
        cam.target = guy.target_postition();
        guy.update();
        guy.DrawHitbox(isColliding);
        EndMode2D();
        EndDrawing();
    }

    grid.~Grid();
    CloseWindow();

    return 0;
}
