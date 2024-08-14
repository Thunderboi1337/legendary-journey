#include "health.h"

Health::Health()
{

    CurrentHealth = 100.f;
    GameOver = false;
    Dead = false;
}

Health::~Health()
{
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

void Health::DisplayHealth(void)
{

    DrawRectangle(10, 10, CurrentHealth, 20, GREEN);
}
