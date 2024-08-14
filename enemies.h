#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include <vector>
#include "health.h"

class Enemies
{
private:
public:
    Enemies();
    ~Enemies();

    Health health;

    Vector2 enemies_position;
    int enemies_speed;

    void render();
    void move(Vector2 guy_position, const std::vector<Rectangle> &obstacles);
    void DrawHitbox(bool isColliding);
    Rectangle GetRect();
    void damage(void);
    void respawn(void);

    Texture2D sprite;

    Rectangle frameRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frameCounter;
    bool facingRight;
};

#endif