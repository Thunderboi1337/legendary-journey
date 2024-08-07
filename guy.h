#ifndef GUY_H
#define GUY_H

#include <iostream>
#include <raylib.h>

class Guy
{
public:
    Guy();
    ~Guy();

    void input(void);
    void update(void);
    Vector2 target_postition();

    Rectangle GetRect();
    void DrawHitbox(bool isColliding);

    int player_speed;
    Vector2 player_position;

private:
};

#endif