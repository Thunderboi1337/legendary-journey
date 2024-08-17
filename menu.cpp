#include "menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define BUTTON_WIDTH 240
#define BUTTON_HEIGHT 60

Menu::Menu()
{
    menu_options = INIT;
    Knight = LoadTexture("knight.png");
    Slime = LoadTexture("slime_green.png");

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    // Knight animation variables
    knightSwitchSide = false;
    knightFramesSpeed = 10;
    knightCurrentFrame = 0;
    knightFrameCounter = 0;
    knightFrameRec = {0.0f, 0.0f, (float)Knight.width / 8, (float)Knight.height / 8};
    knightXPos = 800;   // Initial X position of Knight
    knightSpeed = 2.0f; // Speed of movement for Knight

    // Slime animation variables
    slimeFramesSpeed = 10;
    slimeCurrentFrame = 0;
    slimeFrameCounter = 0;
    slimeFrameRec = {0.0f, 0.0f, (float)Slime.width / 4, (float)Slime.height / 3};
    slimeXPos = 900;   // Initial X position of Slime
    slimeSpeed = 2.0f; // Speed of movement for Slime
}

Menu::~Menu()
{
    UnloadTexture(Knight);
    UnloadTexture(Slime);
}

void Menu::render(void)
{
    BeginDrawing();

    // Set a vertical gradient background
    for (int y = 0; y < screenHeight; y++)
    {
        Color color = Fade(DARKPURPLE, (float)y / screenHeight);
        DrawLine(0, y, screenWidth, y, color);
    }

    // Set styles for buttons
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER); // Center text
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x4CAF50FF);     // Normal state: green
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x3D8B40FF);    // Pressed state: even darker green
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x388E3CFF);   // Border color normal
    GuiSetStyle(BUTTON, BORDER_WIDTH, 2);
    GuiSetStyle(BUTTON, TEXT_SIZE, 100); // Larger text size for buttons

    // Add title text with a shadow effect
    DrawTextEx(GetFontDefault(), "THIS IS A GAME", (Vector2){(screenWidth / 2) - 195, 85}, 50, 2, DARKGREEN);
    DrawTextEx(GetFontDefault(), "THIS IS A GAME", (Vector2){(screenWidth / 2) - 190, 80}, 50, 2, GREEN);

    update_positions(); // Update sprite positions

    render_knight();
    render_slime();

    // Draw a separator line
    DrawLine(screenWidth / 2 - 150, 140, screenWidth / 2 + 150, 140, DARKGRAY);

    // Draw buttons with updated styles and larger text
    if (GuiButton((Rectangle){(screenWidth / 2) - 120, 180, BUTTON_WIDTH, BUTTON_HEIGHT}, "Start Game"))
    {
        menu_options = START_GAME;
    }

    if (GuiButton((Rectangle){(screenWidth / 2) - 120, 260, BUTTON_WIDTH, BUTTON_HEIGHT}, "Quit"))
    {
        menu_options = QUIT;
    }

    // Draw a footer text
    DrawText("Press ESC to exit", screenWidth - 220, screenHeight - 40, 20, GRAY);

    EndDrawing();
}

void Menu::update_positions(void)
{
    // Update Knight's position
    knightXPos -= knightSpeed;
    if (knightXPos + knightFrameRec.width * 4.0f < 0) // Check if the sprite is off the left side
    {
        knightXPos = screenWidth; // Reset to the right side of the screen
    }

    // Update Slime's position
    slimeXPos -= slimeSpeed;
    if (slimeXPos + slimeFrameRec.width * 4.0f < 0) // Check if the sprite is off the left side
    {
        slimeXPos = screenWidth + 35; // Reset to the right side of the screen
    }
}

void Menu::render_knight(void)
{
    knightFrameCounter++;

    if (knightFrameCounter >= (60 / knightFramesSpeed))
    {
        knightFrameCounter = 0;
        knightCurrentFrame++;

        if (knightCurrentFrame > 8)
        {
            knightCurrentFrame = 0;
            knightSwitchSide = !knightSwitchSide;
        }
        if (knightSwitchSide)
        {
            knightFrameRec.y = 2 * (float)Knight.height / 8;
            knightFrameRec.x = (float)knightCurrentFrame * (float)Knight.width / 8;
        }
        else
        {
            knightFrameRec.y = 3 * (float)Knight.height / 8;
            knightFrameRec.x = (float)(knightCurrentFrame - 8) * (float)Knight.width / 8;
        }
    }

    Rectangle knightFlippedFrameRec = knightFrameRec;
    knightFlippedFrameRec.width *= -1;

    DrawTexturePro(Knight, knightFlippedFrameRec, Rectangle{knightXPos, 330, knightFrameRec.width * 4.0f, knightFrameRec.height * 4.0f},
                   {knightFrameRec.width / 2, knightFrameRec.height / 2}, 0.0f, WHITE);
}

void Menu::render_slime(void)
{
    slimeFrameCounter++;

    if (slimeFrameCounter >= (60 / slimeFramesSpeed))
    {
        slimeFrameCounter = 0;
        slimeCurrentFrame++;

        if (slimeCurrentFrame > 4)
            slimeCurrentFrame = 0;

        slimeFrameRec.x = (float)slimeCurrentFrame * (float)Slime.width / 4;
        slimeFrameRec.y = 1 * (float)Slime.height / 3;
    }

    Rectangle slimeFlippedFrameRec = slimeFrameRec;
    slimeFlippedFrameRec.width *= -1;

    DrawTexturePro(Slime, slimeFlippedFrameRec, Rectangle{slimeXPos, 343, slimeFrameRec.width * 4.0f, slimeFrameRec.height * 4.0f},
                   {slimeFrameRec.width / 2, slimeFrameRec.height / 2}, 0.0f, WHITE);
}

MenuOptions Menu::getOptions(void)
{
    return menu_options;
}
