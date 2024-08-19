#include "guy.h"

Guy::Guy()
{
    sprite = LoadTexture("knight.png");

    health = std::make_unique<Health>();

    player_speed = 3;
    player_position = {1900, 1970};

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 8, (float)sprite.height / 8};

    player_state = IDLE;

    facingRight = true;
}

Guy::~Guy()
{
    UnloadTexture(sprite);
}

void Guy::input(const std::vector<Rectangle> &obstacles)
{
    Vector2 new_position = player_position; // Start with the current position

    if (currentFrame <= 2 && player_state == HITS)
    {
    }
    else
    {

        player_state = IDLE;

        // Handle normal movement
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            new_position.y -= player_speed;
            player_state = RUNNING;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            new_position.y += player_speed;
            player_state = RUNNING;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            new_position.x -= player_speed;
            player_state = RUNNING;
            facingRight = false;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            new_position.x += player_speed;
            player_state = RUNNING;
            facingRight = true;
        }
        // This movment made the game to easy, want to bring it back later. But for now, no rolling. I was also a good way to check the map for bugs hehe
        /*    // Handle roll movement
           if (IsKeyDown(KEY_W) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT_SHIFT))
           {
               new_position.y -= player_speed * 5;
               player_state = ROLL;
           }

           if (IsKeyDown(KEY_S) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT_SHIFT))
           {
               new_position.y += player_speed * 5;
               player_state = ROLL;
           }
           if (IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
           {
               new_position.x -= player_speed * 5;
               player_state = ROLL;
               facingRight = false;
           }
           if (IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT))
           {
               new_position.x += player_speed * 5;
               player_state = ROLL;
               facingRight = true;
           } */
    }
    // Create a rectangle representing the new position
    Rectangle new_rectx = {new_position.x, player_position.y, 15, 20};
    Rectangle new_recty = {player_position.x, new_position.y, 15, 20};

    // Check for collisions at the new position
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
        player_position.x = new_position.x;
    }
    if (collision_y != 1)
    {

        player_position.y = new_position.y;
    }
}

void Guy::Movement(void)
{
    frameCounter++;

    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame++;

        if (currentFrame > 8)
            currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sprite.width / 8;
    }

    if (player_state == IDLE)
    {
        if (currentFrame >= IDLE_FRAME_COUNT)
            currentFrame = 0; // Loop the idle animation

        frameRec.y = 0;
        frameRec.x = (float)currentFrame * (float)sprite.width / 8; // Assuming idle frames are in the first row
    }
    else if (player_state == RUNNING)
    {
        if (currentFrame < 8)
        {
            // First 8 frames (0 to 7) are on the first row of the run animation
            frameRec.y = 2 * (float)sprite.height / 8;
            frameRec.x = (float)currentFrame * (float)sprite.width / 8;
        }
        else
        {
            // Next 8 frames (8 to 15) are on the second row of the run animation
            frameRec.y = 3 * (float)sprite.height / 8;
            frameRec.x = (float)(currentFrame - 8) * (float)sprite.width / 8;
        }
    }
    /*  else if (player_state == ROLL)
     {
         frameRec.y = 5 * (float)sprite.height / 8; // Third row for running animation
         frameRec.x = (float)currentFrame * (float)sprite.width / 8;
     } */
    else if (player_state == HITS)
    {
        if (currentFrame >= IDLE_FRAME_COUNT)
            currentFrame = 0; // Loop the idle animation

        frameRec.y = 6 * (float)sprite.height / 8; // Third row for running animation
        frameRec.x = (float)currentFrame * (float)sprite.width / 8;
    }

    float scaleFactor = 1.5f;

    if (facingRight)
    {
        Vector2 adjustedPosition = player_position;
        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sprite centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sprite, frameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, 0.0f, WHITE);
    }
    else
    {
        // Flip the sprite by drawing with a negative width
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width *= -1; // Invert the width

        Vector2 adjustedPosition = player_position;
        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sprite centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sprite, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, 0.0f, WHITE);
    }
}

void Guy::damage(void)
{
    if (player_state != HITS)
    {
        health->Damage(true);
        player_state = HITS;
        currentFrame = 0;
    }
}

void Guy::health_bar(void)
{
    health->DisplayHealth();
}

void Guy::render(void)
{
    Movement();
}

Vector2 Guy::target_postition()
{

    return player_position;
}

bool Guy::isDead(void)
{
    return health->isDead();
}

void Guy::respawn(void)
{
    health->setDead(false);
    health->setCurrentHealth(100.f);
    player_position = {1900, 1970};
    health->setHealthAmount(10);
}

Rectangle Guy::GetRect()
{
    return Rectangle{player_position.x, player_position.y, 15, 20};
}

bool Guy::IsFacingRight(void)
{
    return facingRight;
}

enum PlayerState Guy::GetPlayerState(void)
{
    return player_state;
}

void Guy::DrawHitbox(bool isColliding)
{
    Color outlinecolor = isColliding ? RED : BLACK;
    DrawRectangleLinesEx(GetRect(), 3, outlinecolor);
}