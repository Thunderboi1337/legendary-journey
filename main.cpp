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
    Attack attack = Attack();
    Enemies enemies = Enemies();
    Objects trees = Objects("trees.json");
    Objects objects = Objects("maps.json");

    Camera2D cam = {0};
    cam.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    trees.GetWorldObjects();
    objects.GetWorldObjects();

    std::vector<Rectangle> objcts = objects.GetObjects();
    std::vector<Rectangle> treeObjects = trees.GetObjects();

    objcts.insert(objcts.end(), treeObjects.begin(), treeObjects.end());

    while (!WindowShouldClose())
    {

        guy.input(objcts);
        attack.input();

        enemies.move(guy.target_postition(), objcts);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(cam);

        world.render();
        cam.target = guy.target_postition();

        guy.render();
        attack.render(guy.target_postition(), guy.IsFacingRight());
        enemies.render();
        world.render_trees();

        if (CheckCollisionRecs(attack.GetRect(), enemies.GetRect()))
        {
            enemies.damage();
        }
        if (CheckCollisionRecs(guy.GetRect(), enemies.GetRect()))
        {
            guy.damage();
        }

        attack.RemoveHitbox(true);

        EndMode2D();

        guy.health_bar();

        if (guy.isDead())
        {
            ClearBackground(RAYWHITE);
            DrawText("GAME OVER!", (GetScreenWidth() / 2.0f) - 120, GetScreenHeight() / 2.0f, 40, DARKGRAY);

            if (IsKeyDown(KEY_ENTER))
            {
                guy.respawn();
                enemies.respawn();
            }
        }

        EndDrawing();
    }

    world.~World();
    guy.~Guy();
    objects.~Objects();
    enemies.~Enemies();

    CloseWindow();

    return 0;
}
