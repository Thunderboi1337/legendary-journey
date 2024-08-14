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

    void input(void);
    void render(Vector2 plater_position, bool facingRight);
    void RemoveHitbox(bool isColliding);
    void damage(Vector2 plater_position, bool facingRight);

    Rectangle GetRect();

    Texture2D sword;
    Rectangle frameRec;
    Rectangle damage_hitbox;

    // Animation variables
    int player_speed;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter;

    bool attackRight;
    int screenWidth;
};

#endif