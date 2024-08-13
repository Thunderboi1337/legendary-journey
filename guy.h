#ifndef GUY_H
#define GUY_H

#include <iostream>
#include <raylib.h>
#include <vector>

#define IDLE_FRAME_COUNT 4

enum PlayerState
{
    IDLE,
    RUNNING,
    ROLL,
};

class Guy
{
public:
    Guy();
    ~Guy();

    void input(const std::vector<Rectangle> &obstacles);
    void render(void);
    void DrawHitbox(bool isColliding);
    void Movement(void);

    Vector2 target_postition();
    Rectangle GetRect();

    Vector2 player_position;
    Texture2D sprite;
    Rectangle frameRec;

    int player_speed;
    // Animation variables
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter; // Current frame in the animation

    PlayerState player_state;
    bool facingRight;

private:
};

#endif