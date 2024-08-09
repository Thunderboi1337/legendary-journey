#include "enemies.h"
#include "guy.h"

Enemies::Enemies()
{
    sprite = LoadTexture("slime_green.png");

    enemies_position = {811, 800};
    enemies_speed = 2;

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 8, (float)sprite.height / 8};

    facingRight = true;
}

Enemies::~Enemies()
{
    UnloadTexture(sprite);
}

void Enemies::render()
{
    frameCounter++;

    // Update the current frame based on the frame speed
    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame++;

        // Loop back the frame when reaching the end
        if (currentFrame > 4)
            currentFrame = 0;

        // Set the frameRec for the current frame
        frameRec.x = (float)currentFrame * (float)sprite.width / 8;
    }

    // Set the frameRec y-position to point to the correct animation row
    frameRec.y = 2 * (float)sprite.height / 8;

    Vector2 adjustedPosition = enemies_position;

    if (facingRight)
    {
        adjustedPosition.x -= (frameRec.width - 26); // Adjust to keep sprite centered
        adjustedPosition.y -= 10;                    // Adjust vertical positioning if needed

        DrawTextureRec(sprite, frameRec, adjustedPosition, WHITE);
    }
    else
    {
        // Flip the sprite by drawing with a negative width
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width *= -1; // Invert the width

        adjustedPosition.x -= (frameRec.width - 26); // Adjust to keep sprite centered
        adjustedPosition.y -= 10;                    // Adjust vertical positioning if needed

        DrawTextureRec(sprite, flippedFrameRec, adjustedPosition, WHITE);
    }

    // Draw hitbox for debugging
    DrawRectangle(enemies_position.x, enemies_position.y, 20, 20, BLUE);
}

void Enemies::move(Vector2 guy_position, const std::vector<Rectangle> &obstacles)
{
    Vector2 new_position = enemies_position;

    if (enemies_position.x < guy_position.x)
    {
        new_position.x += enemies_speed;
        facingRight = true;
    }
    else if (enemies_position.x > guy_position.x)
    {
        new_position.x -= enemies_speed;
        facingRight = false;
    }

    if (enemies_position.y < guy_position.y)
    {
        new_position.y += enemies_speed;
    }
    if (enemies_position.y > guy_position.y)
    {
        new_position.y -= enemies_speed;
    }

    Rectangle new_rectx = {new_position.x, enemies_position.y, 20, 20};
    Rectangle new_recty = {enemies_position.x, new_position.y, 20, 20};

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
        enemies_position.x = new_position.x;
    }
    if (collision_y != 1)
    {

        enemies_position.y = new_position.y;
    }
}

Rectangle Enemies::GetRect()
{
    return Rectangle{enemies_position.x, enemies_position.y, 20, 20};
}

void Enemies::DrawHitbox(bool isColliding)
{
    Color outlinecolor = isColliding ? RED : BLACK;
    DrawRectangleLinesEx(GetRect(), 3, outlinecolor);
}
