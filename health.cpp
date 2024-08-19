#include "health.h"

Health::Health()
{
    heartRotation = LoadTexture("heart.rotate.png");
    heart = LoadTexture("heart.png");

    CurrentHealth = 100;
    GameOver = false;
    Dead = false;

    health_level = START_HEART;

    currentHEARTS = 10;

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)heartRotation.width / 12, (float)heartRotation.height};
}

Health::~Health()
{
    UnloadTexture(heartRotation);
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
        if (currentFrame > 11)
            currentFrame = 0;
    }

    switch (health_level)
    {
    case START_HEART:

        frameRec.x = (float)currentFrame * (float)heartRotation.width / 12;

        for (int i = 0; i < 10; i++)
        {
            DrawTexturePro(heartRotation, frameRec, Rectangle{20.f + 30.f * i, 20.f, frameRec.width * 1.0f, frameRec.height * 1.0f},
                           {frameRec.width / 2, frameRec.height / 2}, 0.0f, WHITE);
        }

        if (currentFrame == 11)
        {
            health_level = HEARTS;
        }

        break;

    case HEARTS:
        frameRec.x = (float)currentFrame * (float)heart.width;

        for (int i = 0; i < currentHEARTS; i++)
        {
            DrawTexturePro(heart, frameRec, Rectangle{20.f + 30.f * i, 20.f, frameRec.width * 1.0f, frameRec.height * 1.0f},
                           {frameRec.width / 2, frameRec.height / 2}, 0.0f, WHITE);
        }
        break;

    default:
        break;
    }
}

void Health::Damage(bool hit)
{
    if (hit)
    {
        CurrentHealth -= 10;
        currentHEARTS -= 1;
        if (CurrentHealth <= 0)
        {
            Dead = true;
        }
    }
}

bool Health::isDead(void)
{
    return Dead;
}

void Health::setDead(bool DeadState)
{
    Dead = DeadState;
}

void Health::setCurrentHealth(float Health)
{

    CurrentHealth = Health;
}

void Health::setHealthAmount(int Hearts)
{
    currentHEARTS = Hearts;
}
