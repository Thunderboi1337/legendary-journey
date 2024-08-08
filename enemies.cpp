#include "enemies.h"
#include "guy.h"

Enemies::Enemies()
{
    enemies_position = {811, 800};
    enemies_speed = 2;
}

Enemies::~Enemies()
{
}

void Enemies::render()
{

    DrawRectangle(enemies_position.x, enemies_position.y, 20, 20, BLUE);
}

void Enemies::move(Vector2 guy_position)
{

    if (enemies_position.x < guy_position.x)
    {
        enemies_position.x += enemies_speed;
    }
    else if (enemies_position.x > guy_position.x)
    {
        enemies_position.x -= enemies_speed;
    }

    if (enemies_position.y < guy_position.y)
    {
        enemies_position.y += enemies_speed;
    }
    else if (enemies_position.y > guy_position.y)
    {
        enemies_position.y -= enemies_speed;
    }
}
