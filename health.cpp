#include "health.h"

Health::Health()
{
    sprite = LoadTexture("heart.png");

    CurrentHealth = 100.f;
    GameOver = false;
    Dead = false;

    health_level = FIVE_HEART;

    framesSpeed = 5;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 4, (float)sprite.height / 3};
}

Health::~Health()
{
    UnloadTexture(sprite);
}

void Health::DisplayHealth(void)
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

    switch (health_level)
    {
    case FIVE_HEART:
        for (int i = 0; i < 5; i++)
        {
            DrawTexture(sprite, 10 * i, 10, WHITE);
        }
        break;

    case FOUR_HEART:
        break;

    default:
        break;
    }

    DrawRectangle(10, 10, CurrentHealth, 20, GREEN);
}

void Health::Damage(bool hit)
{
    if (hit)
    {
        CurrentHealth -= 2.f;
        if (CurrentHealth <= 0)
        {
            Dead = true;
        }
    }
}
