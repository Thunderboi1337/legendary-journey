#ifndef HEALTH_H
#define HEALTH_H

#include "raylib.h"

enum HealthLevel
{
    START_HEART,
    HEARTS
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
    Texture2D heart;

    int currentHEARTS;

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