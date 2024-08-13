#include <iostream>
#include <raylib.h>
#include <vector>
#include "guy.h"
#include "world.h"
#include "objects.h"
#include "enemies.h"
#include "attack.h"

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
    Objects objects = Objects("maps.json");
    Objects trees = Objects("trees.json");
    Enemies enemies = Enemies();
    Attack attack = Attack();

    Camera2D cam = {0};
    cam.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    objects.GetWorldObjects();
    trees.GetWorldObjects();

    while (!WindowShouldClose())
    {
        std::vector<Rectangle> objcts;
        objcts = objects.GetObjects();
        std::vector<Rectangle> treeObjects = trees.GetObjects();
        objcts.insert(objcts.end(), treeObjects.begin(), treeObjects.end());

        guy.input(objcts);
        attack.input();
        bool isColliding = objects.isColliding(guy.GetRect());
        bool isEColliding = objects.isColliding(enemies.GetRect());

        enemies.move(guy.target_postition(), objcts);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode2D(cam);
        trees.render();
        objects.render();
        world.render();
        cam.target = guy.target_postition();

        if (CheckCollisionRecs(guy.GetRect(), enemies.GetRect()))
        {
            enemies.DrawHitbox(true);
            guy.DrawHitbox(true);
            char bang[] = "BANG";
            Vector2 pos = guy.target_postition();
            DrawText(bang, pos.x, pos.y - 30, 20, RED);
        }

        guy.render();
        attack.render(guy.target_postition());

        // enemies.render();

        world.render_trees();

        char position_text[50];
        sprintf(position_text, "X: %.2f, Y: %.2f", guy.player_position.x, guy.player_position.y);

        EndMode2D();

        DrawText(position_text, 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    world.~World();
    guy.~Guy();
    objects.~Objects();
    enemies.~Enemies();
    CloseWindow();

    return 0;
}
