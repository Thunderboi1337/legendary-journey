#ifndef HEALTH_H
#define HEALTH_H

#include "raylib.h"

enum HealthLevel
{
    ONE_HEART = 20,
    TWO_HEART = 40,
    THREE_HEART = 60,
    FOUR_HEART = 80,
    FIVE_HEART = 100
}

class Health
{
private:
public:
    Health();
    ~Health();

    float CurrentHealth;
    bool GameOver;
    bool Dead;

    HealthLevel health_level;

    Texture2D sprite;

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