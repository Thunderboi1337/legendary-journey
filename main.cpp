#include <iostream>
#include <raylib.h>
#include <vector>
#include "guy.h"
#include "world.h"
#include "objects.h"
#include "enemies.h"

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
    World world = World();
    Objects objects = Objects();
    Enemies enemies = Enemies();

    Camera2D cam = {0};
    cam.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    objects.GetWorldObjects();

    while (!WindowShouldClose())
    {
        guy.input(objects.GetObjects());
        bool isColliding = objects.isColliding(guy.GetRect());

        enemies.move(guy.target_postition());

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode2D(cam);

        objects.render();
        world.render();
        cam.target = guy.target_postition();
        guy.render();
        enemies.render();
        guy.DrawHitbox(isColliding);

        char position_text[50];
        sprintf(position_text, "X: %.2f, Y: %.2f", guy.player_position.x, guy.player_position.y);

        EndMode2D();

        DrawText(position_text, 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    world.~World();
    guy.~Guy();
    objects.~Objects();
    CloseWindow();

    return 0;
}
