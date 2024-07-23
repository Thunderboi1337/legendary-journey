#ifndef GUY_H
#define GUY_H

#include <iostream>
#include <raylib.h>

class Guy
{
public:
    Guy();
    ~Guy();

    bool cooldowns(double interval);
    void input(void);
    void update(void);
    Vector2 target_postition();

    static bool dash_active;

    double last_update_time;
    const int player_speed = 3;
    Vector2 player_position;

private:
};

#endif