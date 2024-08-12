#include "guy.h"

Guy::Guy()
{
    sprite = LoadTexture("knight.png");
    sword = LoadTexture("machete_iron.png");

    player_speed = 3;
    player_position = {811, 973};

    framesSpeed = 10;
    currentFrame = 0;
    framesCounter = 0;
    frameCounter = 0;

    frameRec = {0.0f, 0.0f, (float)sprite.width / 8, (float)sprite.height / 8};

    player_state = IDLE;
    attack_state = RESTING;
    facingRight = true;
}

Guy::~Guy()
{
    UnloadTexture(sprite);
    UnloadTexture(sword);
}

void Guy::input(const std::vector<Rectangle> &obstacles)
{
    Vector2 new_position = player_position; // Start with the current position

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

    // Handle sprint movement
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
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        attack_state = SWORD;
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

void Guy::render(void)
{
    Movement();
    Attack();
}

Vector2 Guy::target_postition()
{

    return player_position;
}

Rectangle Guy::GetRect()
{
    return Rectangle{player_position.x, player_position.y, 15, 20};
}

void Guy::DrawHitbox(bool isColliding)
{
    Color outlinecolor = isColliding ? RED : BLACK;
    DrawRectangleLinesEx(GetRect(), 3, outlinecolor);
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
    else if (player_state == ROLL)
    {
        frameRec.y = 5 * (float)sprite.height / 8; // Third row for running animation
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

void Guy::Attack(void)
{

    frameCounter++;

    if (frameCounter >= (60 / framesSpeed))
    {
        frameCounter = 0;
        currentFrame = 0;

        if (currentFrame > 4)
            currentFrame = 0;

        frameRec.x = (float)currentFrame * (float)sword.width;
    }

    Vector2 adjustedPosition = player_position;
    float scaleFactor = 1.5f;
    float rotation = 0.0f;

    if (attack_state == RESTING)
    {

        // First 8 frames (0 to 7) are on the first row of the run animation
        frameRec.x = (float)currentFrame * (float)sword.width;
        rotation = 90.0f;
        adjustedPosition.x += 55;
        adjustedPosition.y += 10;
    }
    else if (attack_state == SWORD)
    {
        frameRec.y = 2 * (float)sword.height / 4;
        frameRec.x = (float)currentFrame * (float)sword.width / 4;
        if (currentFrame == 0)
        {
            adjustedPosition.x -= 10; // left to right
            adjustedPosition.y -= 5;  // up and down
        }
        else if (currentFrame == 1)
        {
            rotation = 15.0f;
            adjustedPosition.y -= 5;
        }
        else if (currentFrame == 2)
        {
            rotation = -45.0f;
            adjustedPosition.x += 20; // left to right
            adjustedPosition.y -= 5;
        }
        else if (currentFrame == 3)
        {
            rotation = -90.0f;
            adjustedPosition.x += 40;
            adjustedPosition.y -= 10;
        }
    }

    if (facingRight)
    {

        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sprite centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, frameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
    else
    {
        // Flip the sprite by drawing with a negative width
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width *= -1; // Invert the width

        adjustedPosition.x -= (frameRec.width - 20) * scaleFactor; // Adjust to keep sprite centered
        adjustedPosition.y -= 15 * scaleFactor;

        DrawTexturePro(sword, flippedFrameRec, Rectangle{adjustedPosition.x, adjustedPosition.y, frameRec.width * scaleFactor, frameRec.height * scaleFactor},
                       {0, 0}, rotation, WHITE);
    }
}
