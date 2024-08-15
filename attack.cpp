#include "attack.h"
#include "iostream"
Attack::Attack()
{

    sword = LoadTexture("machete_iron.png");

    player_speed = 3;

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sword.width / 4, (float)sword.height / 2};
    damage_hitbox = {0, 0, 0, 0};

    attack_state = RESTING;
    attackRight = true;
    attackAbove = false;
    attackBellow = false;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
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

        Vector2 mousePosition = GetMousePosition();

        if (CheckCollisionPointTriangle(mousePosition, {0, 0}, {screenWidth / 2, screenHeight / 2}, {screenWidth, 0})) // Check if the mouse is in the "above" triangle
        {
            attackAbove = true;
            attackBellow = false;
            attackRight = false;
            std::cout << "attack above" << attackAbove << std::endl;
        }
        else if (CheckCollisionPointTriangle(mousePosition, {0, 450}, {800, 450}, {screenWidth / 2, screenHeight / 2})) // Check if the mouse is in the "below" triangle
        {
            attackBellow = true;
            attackAbove = false;
            attackRight = false;
            std::cout << "attack bellow" << attackBellow << std::endl;
        }
        else if (CheckCollisionPointTriangle(mousePosition, {800, 450}, {800, 0}, {screenWidth / 2, screenHeight / 2})) // Check if the mouse is in the "right" triangle
        {
            attackRight = true;
            attackAbove = false;
            attackBellow = false;
            std::cout << "attack right" << attackRight << std::endl;
        }
        else if (CheckCollisionPointTriangle(mousePosition, {0, 0}, {0, 450}, {screenWidth / 2, screenHeight / 2})) // Otherwise, it's in the "left" triangle
        {
            attackRight = false;
            attackAbove = false;
            attackBellow = false;
            std::cout << "attack left" << attackRight << std::endl;
        }
    }
}

void Attack::render(Vector2 player_position, bool facingRight)
{
    Vector2 adjustedPosition = player_position;
    float scaleFactor = 1.5f;
    float rotation = 0.0f;

    frameCounter++;

    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame++;

        if (currentFrame > 3 || attack_state == RESTING)
            currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sword.width;
    }

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
        damage(player_position);
    }

    Rectangle flippedFrameRec = frameRec; // Flip the sword by drawing with a negative width

    if (attackAbove)
    {

        if (attack_state == SWORD)
        {
            flippedFrameRec.width *= -1;

            if (currentFrame == 0)
            {
                adjustedPosition.x -= 25; // left to right
                adjustedPosition.y += 50; // up and down
                rotation += 0;            // DONE
            }

            else if (currentFrame == 1)
            {
                adjustedPosition.x -= 25; // left to right
                adjustedPosition.y += 50; // up and down
                rotation += 0;            // Done
            }
            else if (currentFrame == 2)
            {

                adjustedPosition.x -= 25; // left to right
                adjustedPosition.y += 57; // up and down
                rotation += 0;            // Done
            }
            else if (currentFrame == 3)
            {

                adjustedPosition.x -= 26; // left to right
                adjustedPosition.y += 57; // up and down
                rotation += 0;            // Done

                attack_state = RESTING;
            }
        }

        // Flip the sword by drawing with a negative width

        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
    else if (attackBellow)
    {
        if (attack_state == RESTING && !facingRight)
        {
            adjustedPosition.x -= 20;
            flippedFrameRec.width *= -1; // Invert the width
        }
        else if (attack_state == SWORD)
        {

            if (currentFrame == 0)
            {
                adjustedPosition.x += 60; // left to right
                adjustedPosition.y -= 5;  // up and down
                rotation += 150;          // DONE
            }

            else if (currentFrame == 1)
            {
                adjustedPosition.x += 60; // DONE
                adjustedPosition.y += 5;
                rotation += 150;
            }
            else if (currentFrame == 2)
            {

                adjustedPosition.x += 75; // left to right
                adjustedPosition.y += 10; // Done
                rotation += 180;
            }
            else if (currentFrame == 3)
            {

                adjustedPosition.x += 75; // left to right
                adjustedPosition.y += 10;
                rotation += 180; // Done

                attack_state = RESTING;
            }
        }
        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }

    if (attackRight)
    {

        if (attack_state == RESTING && !facingRight)
        {
            adjustedPosition.x -= 20;
            flippedFrameRec.width *= -1; // Invert the width
        }
        else if (attack_state == SWORD)
        {

            if (currentFrame == 0)
            {
                adjustedPosition.x += 60; // left to right
                adjustedPosition.y -= 5;  // up and down
                rotation += 75;           // DONE
            }

            else if (currentFrame == 1)
            {
                adjustedPosition.x += 60; // DONE
                adjustedPosition.y += 5;
                rotation += 75;
            }
            else if (currentFrame == 2)
            {

                adjustedPosition.x += 75; // left to right
                adjustedPosition.y += 10; // Done
                rotation += 90;
            }
            else if (currentFrame == 3)
            {

                adjustedPosition.x += 75; // left to right
                adjustedPosition.y += 10;
                rotation += 90; // Done

                attack_state = RESTING;
            }
        }
        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
    else if (!attackRight)
    {
        if (attack_state == RESTING && !facingRight)
        {
            adjustedPosition.x -= 20;
            flippedFrameRec.width *= -1; // Invert the width
        }
        else if (attack_state == SWORD)
        {
            flippedFrameRec.width *= -1;

            if (currentFrame == 0)
            {
                adjustedPosition.x -= 25; // left to right
                adjustedPosition.y += 50; // up and down
                rotation -= 75;           // DONE
            }

            else if (currentFrame == 1)
            {
                adjustedPosition.x -= 25; // left to right
                adjustedPosition.y += 50; // up and down
                rotation -= 75;           // Done
            }
            else if (currentFrame == 2)
            {

                adjustedPosition.x -= 25; // left to right
                adjustedPosition.y += 57; // up and down
                rotation -= 90;           // Done
            }
            else if (currentFrame == 3)
            {

                adjustedPosition.x -= 26; // left to right
                adjustedPosition.y += 57; // up and down
                rotation -= 90;           // Done

                attack_state = RESTING;
            }
        }

        // Flip the sword by drawing with a negative width

        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sword centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
}

Rectangle Attack::GetRect()
{
    return damage_hitbox;
}

void Attack::RemoveHitbox(bool isColliding)
{
    damage_hitbox = {0, 0, 0, 0};
}

void Attack::damage(Vector2 player_position)
{

    if (attackAbove)
    {
        damage_hitbox = {player_position.x, player_position.y - 40, 25, 30};
    }
    else if (attackBellow)
    {
        damage_hitbox = {player_position.x, player_position.y + 40, 25, 30};
    }

    else if (attackRight)
    {
        damage_hitbox = {player_position.x + 20, player_position.y - 5, 30, 25};
    }
    else if (!attackRight)
    {
        damage_hitbox = {player_position.x - 40, player_position.y - 5, 30, 25};
    }

    DrawRectangleRec(damage_hitbox, RED);
}
