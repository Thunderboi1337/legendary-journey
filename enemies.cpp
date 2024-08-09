#include "enemies.h"
#include "guy.h"

Enemies::Enemies()
{
    sprite = LoadTexture("slime_green.png");

    enemies_position = {811, 800};
    enemies_speed = 2;

    framesSpeed = 5;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 4, (float)sprite.height / 3};

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
        frameRec.x = (float)currentFrame * (float)sprite.width / 4;
    }

    // Set the frameRec y-position to point to the correct animation row
    frameRec.y = 1 * (float)sprite.height / 3;

    Vector2 adjustedPosition = enemies_position;

    // Define the scale factor
    float scaleFactor = 2.0f; // Adjust this value to scale the sprite to your desired size

    if (facingRight)
    {
        adjustedPosition.x -= (frameRec.width - 23) * scaleFactor; // Adjust to keep sprite centered
        adjustedPosition.y -= 16;                                  // Adjust vertical positioning if needed

        DrawTexturePro(sprite, frameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {frameRec.width / 2, frameRec.height / 2}, 0.0f, WHITE);
    }
    else
    {
        // Flip the sprite by drawing with a negative width
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width *= -1; // Invert the width

        adjustedPosition.x -= (frameRec.width - 23) * scaleFactor; // Adjust to keep sprite centered
        adjustedPosition.y -= 16;                                  // Adjust vertical positioning if needed

        DrawTexturePro(sprite, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {frameRec.width / 2, frameRec.height / 2}, 0.0f, WHITE);
    }

    // Draw hitbox for debugging
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
