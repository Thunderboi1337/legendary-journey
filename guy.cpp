#include "guy.h"

Guy::Guy()
{

    player_position = {811, 973};
    player_speed = 3;
}

Guy::~Guy()
{
}

void Guy::input(void)
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
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT_SHIFT))
    {

        player_position.y -= player_speed * 10;
    }
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        player_position.y += player_speed * 10;
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
    {

        player_position.x -= player_speed * 10;
    }
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT))
    {

        player_position.x += player_speed * 10;
    }
}

void Guy::update(void)
{

    char position_text[50];
    sprintf(position_text, "X: %.2f, Y: %.2f", player_position.x, player_position.y);

    DrawRectangle(player_position.x, player_position.y, 20, 20, BLUE);

    DrawText(position_text, 10, 10, 20, DARKGRAY);
}

Vector2 Guy::target_postition()
{

    return player_position;
}

Rectangle Guy::GetRect()
{
    return Rectangle{player_position.x, player_position.y, 20, 20};
}

void Guy::DrawHitbox(bool isColliding)
{
    Color outlinecolor = isColliding ? RED : BLACK;
    DrawRectangleLinesEx(GetRect(), 3, outlinecolor);
}
