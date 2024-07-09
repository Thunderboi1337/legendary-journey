#include <iostream>
#include <raylib.h>

#define FPS 60

const int screenWidth = 800;
const int screenHeight = 450;

static int player_x = 400;
static int player_y = 225;
const int player_speed = 3;

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
    if (IsKeyDown(KEY_W))
    {
        player_y -= player_speed;
    }
    if (IsKeyDown(KEY_S))
    {
        player_y += player_speed;
    }
    if (IsKeyDown(KEY_A))
    {
        player_x -= player_speed;
    }
    if (IsKeyDown(KEY_D))
    {
        player_x += player_speed;
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
    DrawRectangle(player_x, player_y, 20, 20, BLUE);
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
