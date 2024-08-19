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

public:
    Health();
    ~Health();

    void DisplayHealth(void);
    void Damage(bool hit);
    bool isDead(void);
    void setDead(bool DeadState);
    void setCurrentHealth(float Health);
    void setHealthAmount(int Hearts);
};

#endif