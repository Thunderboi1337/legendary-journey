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

    frameRec = {0.0f, 0.0f, (float)sword.width / 4, (float)sword.height / 2};

    attack_state = RESTING;
    facingRight = true;
}

Attack::~Attack()
{
    UnloadTexture(sword);
}

void Attack::input()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        attack_state = SWORD;
        currentFrame = 0;
    }
}

void Attack::render(Vector2 plater_position)
{
    frameCounter++;

    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame++;

        if (currentFrame > 3)
            currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sword.width;
    }

    Vector2 adjustedPosition = plater_position;
    float scaleFactor = 1.5f;
    float rotation = 0.0f;

    if (attack_state == RESTING)
    {

        frameRec.y = (float)sword.height;
        frameRec.x = (float)currentFrame * (float)sword.width;
        adjustedPosition.x += 10; // left to right
    }
    else if (attack_state == SWORD)
    {
        frameRec.y = 2 * (float)sword.height / 4;
        frameRec.x = (float)currentFrame * (float)sword.width / 4;
    }

    if (facingRight)
    {
        if (attack_state == SWORD)
        {
            if (currentFrame == 0)
            {
                adjustedPosition.x += 30; // left to right
                adjustedPosition.y -= 5;  // up and down
                rotation += 30;           // DONE
            }

            else if (currentFrame == 1)
            {
                adjustedPosition.x += 60; // DONE
                adjustedPosition.y += 5;
                rotation += 75;
            }
            else if (currentFrame == 2)
            {

                adjustedPosition.x += 70; // left to right
                adjustedPosition.y += 10;
                rotation += 90;
            }
            else if (currentFrame == 3)
            {

                adjustedPosition.x += 70; // left to right
                adjustedPosition.y += 10;
                rotation += 90;

                attack_state = RESTING;
            }
        }
        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, frameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
    else
    {
        if (attack_state == SWORD)
        {
            if (currentFrame == 0)
            {
                adjustedPosition.x += 30; // left to right
                adjustedPosition.y -= 5;  // up and down
                rotation += 30;           // DONE
            }

            else if (currentFrame == 1)
            {
                adjustedPosition.x += 60; // DONE
                adjustedPosition.y += 5;
                rotation += 75;
            }
            else if (currentFrame == 2)
            {

                adjustedPosition.x += 70; // left to right
                adjustedPosition.y += 10;
                rotation += 90;
            }
            else if (currentFrame == 3)
            {

                adjustedPosition.x += 70; // left to right
                adjustedPosition.y += 10;
                rotation += 90;

                attack_state = RESTING;
            }
        }

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
