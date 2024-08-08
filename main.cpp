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

        objects.render();
        grid.render();
        cam.target = guy.target_postition();
        guy.update();
        guy.DrawHitbox(isColliding);

        sprintf(position_text, "X: %.2f, Y: %.2f", player_position.x, player_position.y);

        EndMode2D();
        EndDrawing();
    }

    grid.~Grid();
    guy.~Guy();
    objects.~Objects();
    CloseWindow();

    return 0;
}
