#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>
#include "guy.h"
#include "world.h"
#include "objects.h"
#include "enemy.h"
#include "attack.h"

#define FPS 60
#define MAX_ENEMY_AMOUNT 30

const int screenWidth = 800;
const int screenHeight = 450;

static int RoundCounter = 0;
static int killcount = 0;
static int RoundAmount = 5;
static int activeEnemies = 5;

void init(void)
{
    InitWindow(screenWidth, screenHeight, "Main window");
    SetTargetFPS(FPS);
}

int main(void)
{
    static int frameCounter;

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

    // Create a vector of unique pointers to Enemy objects
    std::vector<std::unique_ptr<Enemy>> enemies;

    // Create all enemies, but only a subset will be active each round
    for (int i = 0; i < MAX_ENEMY_AMOUNT; ++i)
    {
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
        enemy->setPosition({static_cast<float>(100 + (i * 50)), 400});
        enemies.push_back(std::move(enemy));
    }

    while (!WindowShouldClose())
    {
        frameCounter++;

        if (killcount >= RoundAmount)
        {
            RoundAmount += 5;
            killcount = 0;
            RoundCounter++;
            activeEnemies += 5; // Increase the number of active enemies each round
            if (activeEnemies > MAX_ENEMY_AMOUNT)
            {
                activeEnemies = MAX_ENEMY_AMOUNT; // Cap the number of active enemies
            }
        }

        guy.input(objcts);
        attack.input();

        // Update and render only the active enemies
        for (int i = 0; i < activeEnemies - 1; ++i)
        {
            if (!CheckCollisionRecs(enemies[i]->GetRect(), enemies[i + 1]->GetRect()))
            {
                enemies[i]->move(guy.target_postition(), objcts);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(cam);

        world.render();
        cam.target = guy.target_postition();

        guy.render();
        attack.render(guy.target_postition(), guy.IsFacingRight());

        // Render only the active enemies
        for (int i = 0; i < activeEnemies; ++i)
        {
            enemies[i]->render();
        }

        world.render_trees();

        // Collision checks only for active enemies
        for (int i = 0; i < activeEnemies; ++i)
        {
            if (CheckCollisionRecs(attack.GetRect(), enemies[i]->GetRect()))
            {
                enemies[i]->damage();
            }
            if (frameCounter >= FPS)
            {

                if (CheckCollisionRecs(guy.GetRect(), enemies[i]->GetRect()))
                {
                    guy.damage();

                    frameCounter = 0;
                }
            }
            if (enemies[i]->isDead())
            {
                killcount++;
                enemies[i]->respawn(); // Respawn the enemy
            }
        }

        attack.RemoveHitbox(true);

        EndMode2D();

        char killcount_text[50];
        char roundcounter_text[50];
        sprintf(killcount_text, "KillCount: %d", killcount);
        sprintf(roundcounter_text, "Round: %d", RoundCounter);

        DrawText(killcount_text, 10, 40, 20, DARKGRAY);
        DrawText(roundcounter_text, 10, 60, 20, DARKGRAY);

        guy.health_bar();

        if (guy.isDead())
        {
            ClearBackground(RAYWHITE);
            DrawText("GAME OVER!", (GetScreenWidth() / 2.0f) - 120, (GetScreenHeight() / 2.0f) - 40, 40, DARKGRAY);
            DrawText("[Press Enter to try again]", (GetScreenWidth() / 2.0f) - 130, (GetScreenHeight() / 2.0f) + 20, 20, DARKGRAY);

            if (IsKeyDown(KEY_ENTER))
            {
                guy.respawn();
                for (auto &enemy : enemies)
                {
                    enemy->respawn();
                }
            }
        }
        Vector2 locatio = guy.target_postition();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
