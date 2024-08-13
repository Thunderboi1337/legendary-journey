#include "health.h"

Health::Health()
{

    CurrentHealth = 100f;
}

Health::~Health()
{
}

void Health::Damage(bool hit)
{
    if (hit)
    {
        CurrentHealth -= 20f;
    }
}

void Health::DisplayHealth(void)
{
}
