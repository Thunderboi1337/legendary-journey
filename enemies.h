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

    Texture2D sprite;

    // Animation variables
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter; // Current frame in the animation
    Rectangle frameRec;

    bool facingRight;
};

#endif