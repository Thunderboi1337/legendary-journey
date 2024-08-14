#include <iostream>
#include <raylib.h>
#include <vector>
#include "guy.h"
#include "world.h"
#include "objects.h"
#include "enemy.h" // Renamed from enemies.h
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

    // Vector to hold multiple enemies
    std::vector<Enemy> enemies;

    Enemy enemy = Enemy();
    // Spawning multiple enemies
    for (int i = 0; i < 5; i++) // Spawn 5 enemies as an example
    {

        enemy.setPosition(Vector2{static_cast<float>(i * 240), 100.0f}); // Position enemies with some spacing
        enemies.push_back(enemy);
    }

    while (!WindowShouldClose())
    {
        guy.input(objcts);
        attack.input();

        for (Enemy &enemy : enemies)
        {
            enemy.move(guy.target_postition(), objcts);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(cam);

        world.render();
        cam.target = guy.target_postition();

        guy.render();
        attack.render(guy.target_postition(), guy.IsFacingRight());

        // Render all enemies
        for (Enemy &enemy : enemies)
        {
            enemy.render();
        }

        world.render_trees();

        for (Enemy &enemy : enemies)
        {
            if (CheckCollisionRecs(attack.GetRect(), enemy.GetRect()))
            {
                enemy.damage();
            }
            if (CheckCollisionRecs(guy.GetRect(), enemy.GetRect()))
            {
                guy.damage();
            }
        }

        attack.RemoveHitbox(true);

        EndMode2D();

        guy.health_bar();

        if (guy.isDead())
        {
            ClearBackground(RAYWHITE);
            DrawText("GAME OVER!", (GetScreenWidth() / 2.0f) - 120, (GetScreenHeight() / 2.0f) - 40, 40, DARKGRAY);
            DrawText("[Press Enter to try again]", (GetScreenWidth() / 2.0f) - 130, (GetScreenHeight() / 2.0f) + 20, 20, DARKGRAY);

            if (IsKeyDown(KEY_ENTER))
            {
                guy.respawn();
                for (Enemy &enemy : enemies)
                {
                    enemy.respawn();
                }
            }
        }

        EndDrawing();
    }

    world.~World();
    guy.~Guy();
    objects.~Objects();

    // No need to explicitly call destructors; this is just for illustration
    for (Enemy &enemy : enemies)
    {
        {
            enemy.~Enemy();
        }
    }

    enemies.clear();
    CloseWindow();

    return 0;
}