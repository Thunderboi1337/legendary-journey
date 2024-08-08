#include "guy.h"

Guy::Guy()
{
    sprite = LoadTexture("knight.png");

    player_speed = 3;
    player_position = {811, 973};

    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 3;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 9, (float)sprite.height / 9};
}

Guy::~Guy()
{
    UnloadTexture(sprite);
}

void Guy::input(const std::vector<Rectangle> &obstacles)
{
    Vector2 new_position = player_position; // Start with the current position

    // Handle normal movement
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        new_position.y -= player_speed;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        new_position.y += player_speed;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        new_position.x -= player_speed;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        new_position.x += player_speed;

    // Handle sprint movement
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT_SHIFT))
        new_position.y -= player_speed * 10;
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT_SHIFT))
        new_position.y += player_speed * 10;
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
        new_position.x -= player_speed * 10;
    if (IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT))
        new_position.x += player_speed * 10;

    // Create a rectangle representing the new position
    Rectangle new_rectx = {new_position.x, player_position.y, 20, 20};
    Rectangle new_recty = {player_position.x, new_position.y, 20, 20};

    // Check for collisions at the new position
    int collision_x = 0;
    int collision_y = 0;

    for (const auto &obstacle : obstacles)
    {
        if (CheckCollisionRecs(new_rectx, obstacle))
        {
            collision_x = 1;
            break;
        }
    }
    for (const auto &obstacle : obstacles)
    {
        if (CheckCollisionRecs(new_recty, obstacle))
        {
            collision_y = 1;
            break;
        }
    }

    // Update the player position only if there's no collision
    if (collision_x != 1)
    {
        player_position.x = new_position.x;
    }
    if (collision_y != 1)
    {

        player_position.y = new_position.y;
    }
}

void Guy::render(void)
{

    frameCounter++;

    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame++;

        if (currentFrame > 2)
            currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sprite.width / 8;
    }

    DrawTextureRec(sprite, frameRec, player_position, WHITE);
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
