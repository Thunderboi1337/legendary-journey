#include "attack.h"

Attack::Attack()
{
    sword = LoadTexture("machete_iron.png");

    player_speed = 3;
    player_position = {811, 973};

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 8, (float)sprite.height / 8};

    attack_state = RESTING;
    facingRight = true;
}

Attack::~Attack()
{
    UnloadTexture(sprite);
}

void Attack::input(const std::vector<Rectangle> &obstacles)
{
}

void Attack::render(void)
{
}

Rectangle Attack::GetRect()
{
    return Rectangle();
}

void Attack::DrawHitbox(bool isColliding)
{
}
