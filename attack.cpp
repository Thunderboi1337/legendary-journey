#include "attack.h"

Attack::Attack()
{
    sword = LoadTexture("machete_iron.png");

    player_speed = 3;
    player_position = {811, 973};

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sword.width / 8, (float)sword.height / 8};

    attack_state = RESTING;
    facingRight = true;
}

Attack::~Attack()
{
    UnloadTexture(sword);
}

void Attack::input(const std::vector<Rectangle> &obstacles)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        attack_state = SWORD;
    }
}

void Attack::render(void)
{
    frameCounter++;

    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame = 0;

        if (currentFrame > 4)
            currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sword.width;
    }

    Vector2 adjustedPosition = player_position;
    float scaleFactor = 1.5f;
    float rotation = 0.0f;

    if (attack_state == RESTING)
    {

        // First 8 frames (0 to 7) are on the first row of the run animation
        frameRec.x = (float)currentFrame * (float)sword.width;
        rotation = 90.0f;
        adjustedPosition.x += 55;
        adjustedPosition.y += 10;
    }
    else if (attack_state == SWORD)
    {
        frameRec.y = 2 * (float)sword.height / 4;
        frameRec.x = (float)currentFrame * (float)sword.width / 4;
        if (currentFrame == 0)
        {
            adjustedPosition.x -= 10; // left to right
            adjustedPosition.y -= 5;  // up and down
        }
        else if (currentFrame == 1)
        {
            rotation = 15.0f;
            adjustedPosition.y -= 5;
        }
        else if (currentFrame == 2)
        {
            rotation = -45.0f;
            adjustedPosition.x += 20; // left to right
            adjustedPosition.y -= 5;
        }
        else if (currentFrame == 3)
        {
            rotation = -90.0f;
            adjustedPosition.x += 40;
            adjustedPosition.y -= 10;
        }
    }

    if (facingRight)
    {

        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, frameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
    else
    {
        // Flip the sword by drawing with a negative width
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width *= -1; // Invert the width

        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
}

Rectangle Attack::GetRect()
{
    return Rectangle();
}

void Attack::DrawHitbox(bool isColliding)
{
}
