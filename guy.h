#ifndef GUY_H
#define GUY_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include "health.h"
#include <memory>

#define IDLE_FRAME_COUNT 4

enum PlayerState
{
    IDLE,
    RUNNING,
    ROLL,
    HITS,
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
    void damage(void);
    void health_bar(void);
    bool isDead(void);
    void respawn(void);

    Vector2 target_postition();
    Rectangle GetRect();
    bool IsFacingRight(void);
    enum PlayerState GetPlayerState(void);

private:
    std::unique_ptr<Health> health;
    Vector2 player_position;
    Texture2D sprite;
    Rectangle frameRec;

    PlayerState player_state;
    bool facingRight;
    int player_speed;

    // Animation variables
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter; // Current frame in the animation
};

#endif