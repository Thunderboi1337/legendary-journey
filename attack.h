#ifndef ATTACK_H
#define ATTACK_H

#include "raylib.h"
#include <vector>

enum AttackState
{
    RESTING,
    SWORD

};

class Attack
{
private:
public:
    Attack();
    ~Attack();

    AttackState attack_state;

    void input(const std::vector<Rectangle> &obstacles);
    void render(void);
    void DrawHitbox(bool isColliding);

    Rectangle GetRect();

    Vector2 player_position;
    Texture2D sword;
    Rectangle frameRec;

    // Animation variables
    int player_speed;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter; // Current frame in the animation
    bool facingRight;
};

#endif