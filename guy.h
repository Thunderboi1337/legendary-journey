#ifndef GUY_H
#define GUY_H

#include <iostream>
#include <raylib.h>
#include <vector>

class Guy
{
public:
    Guy();
    ~Guy();

    void input(const std::vector<Rectangle> &obstacles);
    void render(void);
    Vector2 target_postition();

    Rectangle GetRect();
    void DrawHitbox(bool isColliding);

    int player_speed;
    Vector2 player_position;

    Texture2D sprite;

    // Animation variables
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter; // Current frame in the animation
    Rectangle frameRec;

private:
};

#endif