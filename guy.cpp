#include "guy.h"

bool Guy::dash_active = true;

Guy::Guy()
{
    last_update_time = 0;
    player_position = {400, 225};
}

Guy::~Guy()
{
}

bool Guy::cooldowns(double interval)
{
    double current_time = GetTime();
    if (current_time - last_update_time >= interval)
    {
        last_update_time = current_time;
        return true;
    }

    return false;
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
        if (dash_active)
        {
            player_position.y -= player_speed * 10;
            dash_active = false;
        }
    }
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (dash_active)
        {
            player_position.y += player_speed * 10;
            dash_active = false;
        }
    }
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (dash_active)
        {
            player_position.x -= player_speed * 10;
            dash_active = false;
        }
    }
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (dash_active)
        {
            player_position.x += player_speed * 10;
            dash_active = false;
        }
    }
}

void Guy::update(void)
{
    if (!dash_active)
    {
        if (cooldowns(0.2))
        {
            dash_active = true;
        }
    }

    DrawRectangle(player_position.x - 10, player_position.y - 10, 20, 20, BLUE);

    char position_text[50];
    sprintf(position_text, "X: %.2f, Y: %.2f", player_position.x, player_position.y);

    EndMode2D(); // End applying the camera transformation
}

Vector2 Guy::target_postition()
{

    return player_position;
}
