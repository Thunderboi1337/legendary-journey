#include <iostream>
#include <vector>
#include <memory>
#include "guy.h"
#include "world.h"
#include "objects.h"
#include "enemy.h"
#include "attack.h"
#include "menu.h"
#include "audio.h"

enum Scenes
{
    INTRO,
    MENU,
    GAME,
};

#define FPS 60
#define MAX_ENEMY_AMOUNT 50

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
    SetExitKey(0);
}

int main(void)
{
    static int frameCounter;
    static int j = 1;

    Scenes scenes = MENU;

    init();

    World world = World();
    Attack attack = Attack();
    Objects trees = Objects("newtrees.json");
    Objects objects = Objects("newmap.json");
    Menu menu = Menu();
    Audio audio = Audio();
    Guy guy = Guy();

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
        enemy->setPosition({static_cast<float>(1000 + (i * 50)), 1400});
        enemies.push_back(std::move(enemy));
    }

    MenuOptions menu_options = INIT;

    while (!WindowShouldClose())
    {

        audio.playMusic();

        switch (scenes)
        {
        case INTRO:

            break;
        case MENU:

            menu.render();
            menu_options = menu.getOptions();

            switch (menu_options)
            {
            case START_GAME:
                scenes = GAME;

                guy.respawn();

                RoundAmount = 5;
                killcount = 0;
                RoundCounter = 0;
                activeEnemies = 5;

                for (auto &enemy : enemies)
                {
                    enemy->respawn();
                }

                break;

            case QUIT:

                guy.~Guy();
                world.~World();
                trees.~Objects();

                objects.~Objects();
                attack.~Attack();
                menu.~Menu();
                for (int i = 0; i < MAX_ENEMY_AMOUNT; i++)
                {
                    enemies[i]->~Enemy();
                }
                CloseWindow();

                break;

            default:
                break;
            }

            break;

        case GAME:
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
            for (int i = 0; i < activeEnemies; i++)
            {
                if (!CheckCollisionRecs(enemies[i]->GetRect(), enemies[j]->GetRect()))
                {
                    enemies[i]->move(guy.target_postition(), objcts);
                }
                j = (j + 1) % MAX_ENEMY_AMOUNT;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(cam);

            world.render();
            cam.target = guy.target_postition();

            guy.render();
            attack.render(guy.target_postition(), guy.IsFacingRight());

            // Render only the active enemies
            for (int i = 0; i < activeEnemies; i++)
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
                    enemies[i]->respawn();
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
                const int textSizeGameOver = 40;
                const int textSizeRoundCounter = 20;
                const int textSizeTryAgain = 20;
                const int textSizeBackToMenu = 20;

                // "GAME OVER!" text
                int textWidthGameOver = MeasureText("GAME OVER!", textSizeGameOver);
                DrawText("GAME OVER!", (GetScreenWidth() / 2.0f) - (textWidthGameOver / 2), (GetScreenHeight() / 2.0f) - 40, textSizeGameOver, DARKGRAY);

                // Round counter text
                sprintf(roundcounter_text, "WOW! %d Rounds! COOL!", RoundCounter);
                int textWidthRoundCounter = MeasureText(roundcounter_text, textSizeRoundCounter);
                DrawText(roundcounter_text, (GetScreenWidth() / 2.0f) - (textWidthRoundCounter / 2), (GetScreenHeight() / 2.0f) + 10, textSizeRoundCounter, DARKGRAY);

                // "[Press Enter to try again]" text
                int textWidthTryAgain = MeasureText("[Press Enter to try again]", textSizeTryAgain);
                DrawText("[Press Enter to try again]", (GetScreenWidth() / 2.0f) - (textWidthTryAgain / 2), (GetScreenHeight() / 2.0f) + 40, textSizeTryAgain, DARKGRAY);

                // "[or press ESC to go back to the menu]" text
                int textWidthBackToMenu = MeasureText("[or press ESC to go back to the menu]", textSizeBackToMenu);
                DrawText("[or press ESC to go back to the menu]", (GetScreenWidth() / 2.0f) - (textWidthBackToMenu / 2), (GetScreenHeight() / 2.0f) + 80, textSizeBackToMenu, DARKGRAY);

                if (IsKeyDown(KEY_ENTER))
                {
                    guy.respawn();

                    RoundAmount = 5;
                    killcount = 0;
                    RoundCounter = 0;
                    activeEnemies = 5;

                    for (auto &enemy : enemies)
                    {
                        enemy->respawn();
                    }
                }
                else if (IsKeyPressed(KEY_ESCAPE))
                {
                    menu_options = INIT;
                    scenes = MENU;
                    menu.setOptions(INIT);

                    break;
                }
            }

            EndDrawing();
            break;

        default:
            break;
        }
    }

    guy.~Guy();
    world.~World();
    trees.~Objects();
    objects.~Objects();
    attack.~Attack();
    menu.~Menu();
    for (int i = 0; i < MAX_ENEMY_AMOUNT; i++)
    {
        enemies[i]->~Enemy();
    }
    CloseWindow();
    return 0;
}
