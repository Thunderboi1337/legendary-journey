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

void Enemies::move(Vector2 guy_position, const std::vector<Rectangle> &obstacles)
{
    Vector2 new_position = enemies_position;

    if (enemies_position.x < guy_position.x)
    {
        new_position.x += enemies_speed;
    }
    if (enemies_position.x > guy_position.x)
    {
        new_position.x -= enemies_speed;
    }

    if (enemies_position.y < guy_position.y)
    {
        new_position.y += enemies_speed;
    }
    if (enemies_position.y > guy_position.y)
    {
        new_position.y -= enemies_speed;
    }

    Rectangle new_rectx = {new_position.x, enemies_position.y, 20, 20};
    Rectangle new_recty = {enemies_position.x, new_position.y, 20, 20};

    int collision_x = 0;
    int collision_y = 0;

    for (const auto &obstacle : obstacles)
    {
        if (CheckCollisionRecs(new_rectx, obstacle))
        {
            collision_x = 1;
            break;
        }
    }
    for (const auto &obstacle : obstacles)
    {
        if (CheckCollisionRecs(new_recty, obstacle))
        {
            collision_y = 1;
            break;
        }
    }

    // Update the player position only if there's no collision
    if (collision_x != 1)
    {
        enemies_position.x = new_position.x;
    }
    if (collision_y != 1)
    {

        enemies_position.y = new_position.y;
    }
}

Rectangle Enemies::GetRect()
{
    return Rectangle{enemies_position.x, enemies_position.y, 20, 20};
}

void Enemies::DrawHitbox(bool isColliding)
{
    Color outlinecolor = isColliding ? RED : BLACK;
    DrawRectangleLinesEx(GetRect(), 3, outlinecolor);
}
