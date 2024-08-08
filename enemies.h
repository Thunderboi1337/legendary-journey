#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include <vector>

class Enemies
{
private:
public:
    Vector2 enemies_position;
    int enemies_speed;

    Enemies();
    ~Enemies();

    void render();
    void move(Vector2 guy_position, const std::vector<Rectangle> &obstacles);

    Rectangle GetRect();
    void DrawHitbox(bool isColliding);
};

#endif