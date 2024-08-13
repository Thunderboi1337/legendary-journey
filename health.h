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

    void Damage(bool hit);

    void DisplayHealth(void);
};

#endif