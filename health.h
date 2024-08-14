#ifndef HEALTH_H
#define HEALTH_H

#include "raylib.h"

class Health
{
private:
public:
    Health();
    ~Health();

    float CurrentHealth;
    bool GameOver;
    bool Dead;

    void Damage(bool hit);

    void DisplayHealth(void);
};

#endif