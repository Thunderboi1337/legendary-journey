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

enum AttackState
{
    RESTING,
    SWORD

};

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
    Texture2D sword;

    // Animation variables
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter; // Current frame in the animation
    Rectangle frameRec;

    void Movement(void);
    void Attack(void);

    AttackState attack_state;
    PlayerState player_state;
    bool facingRight;

private:
};

#endif