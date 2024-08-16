#ifndef HEALTH_H
#define HEALTH_H

#include "raylib.h"

enum HealthLevel
{
    ONE_HEART,
    TWO_HEART,
    THREE_HEART,
    FOUR_HEART,
    FIVE_HEART,
    START_HEART
};

class Health
{
private:
public:
    Health();
    ~Health();

    int CurrentHealth;
    bool GameOver;
    bool Dead;

    HealthLevel health_level;

    Texture2D heartRotation;
    Texture2D heartBackground;
    Texture2D heart;

    Rectangle frameRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter;
    bool facingRight;

    void DisplayHealth(void);
    void Damage(bool hit);
};

#endif