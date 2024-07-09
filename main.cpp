#include <iostream>
#include <raylib.h>
#include <vector>

#define FPS 60

const int screenWidth = 800;
const int screenHeight = 450;

const int player_speed = 3;

Vector2 player_position = {400, 225};

Texture2D carl;

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
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        player_position.y -= player_speed;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        player_position.y += player_speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        player_position.x -= player_speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        player_position.x += player_speed;
    }
}

void update(void)
{
    // Any additional game logic updates can be added here
}

void render(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangle(player_position.x, player_position.y, 20, 20, BLUE);
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
