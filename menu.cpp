#include "menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define BUTTON_WIDTH 240
#define BUTTON_HEIGHT 60

// Constructor for the Menu class
Menu::Menu()
{
    menu_options = INIT; // Initialize menu options

    // Load textures for Knight and Slime
    Knight = LoadTexture("knight.png");
    Slime = LoadTexture("slime_green.png");

    // Get screen dimensions
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    // Initialize Knight animation variables
    knightSwitchSide = false;
    knightFramesSpeed = 10;
    knightCurrentFrame = 0;
    knightFrameCounter = 0;
    knightFrameRec = {0.0f, 0.0f, (float)Knight.width / 8, (float)Knight.height / 8}; // Define frame rectangle for Knight
    knightXPos = 800;                                                                 // Initial X position of Knight
    knightSpeed = 2.0f;                                                               // Speed of movement for Knight

    // Initialize Slime animation variables
    slimeFramesSpeed = 10;
    slimeCurrentFrame = 0;
    slimeFrameCounter = 0;
    slimeFrameRec = {0.0f, 0.0f, (float)Slime.width / 4, (float)Slime.height / 3}; // Define frame rectangle for Slime
    slimeXPos = 900;                                                               // Initial X position of Slime
    slimeSpeed = 2.0f;                                                             // Speed of movement for Slime

    // Initialize position for the second Slime, placing it behind the first Slime
    secondSlimeXPos = slimeXPos + slimeFrameRec.width * 4.0f;
}

// Destructor for the Menu class
Menu::~Menu()
{
    // Unload textures to free up resources
    UnloadTexture(Knight);
    UnloadTexture(Slime);
}

// Render method to draw all elements on the screen
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

    // Draw title text with a shadow effect
    DrawTextEx(GetFontDefault(), "THIS IS A GAME", (Vector2){(screenWidth / 2) - 195, 85}, 50, 2, DARKGREEN);
    DrawTextEx(GetFontDefault(), "THIS IS A GAME", (Vector2){(screenWidth / 2) - 190, 80}, 50, 2, GREEN);

    update_positions(); // Update the positions of all moving sprites

    render_knight();       // Render Knight sprite
    render_slime();        // Render the first Slime sprite
    render_second_slime(); // Render the second Slime sprite behind the first one

    // Draw a separator line between buttons
    DrawLine(screenWidth / 2 - 150, 140, screenWidth / 2 + 150, 140, DARKGRAY);

    // Draw buttons with updated styles and larger text
    if (GuiButton((Rectangle){(screenWidth / 2) - 120, 180, BUTTON_WIDTH, BUTTON_HEIGHT}, "Start Game"))
    {
        menu_options = START_GAME; // Set menu option to start game if "Start Game" button is clicked
    }

    if (GuiButton((Rectangle){(screenWidth / 2) - 120, 260, BUTTON_WIDTH, BUTTON_HEIGHT}, "Quit"))
    {
        menu_options = QUIT; // Set menu option to quit if "Quit" button is clicked
    }

    EndDrawing();
}

// Update positions of Knight and both Slime sprites
void Menu::update_positions(void)
{
    // Update Knight's position
    knightXPos -= knightSpeed;
    if (knightXPos + knightFrameRec.width * 4.0f < 0) // Check if Knight is off the left side
    {
        knightXPos = screenWidth; // Reset Knight's position to the right side of the screen
    }

    // Update Slime's position
    slimeXPos -= slimeSpeed;
    if (slimeXPos + slimeFrameRec.width * 4.0f < 0) // Check if Slime is off the left side
    {
        slimeXPos = screenWidth + 35; // Reset Slime's position to the right side of the screen with an offset
    }

    // Update second Slime's position
    secondSlimeXPos -= slimeSpeed;
    if (secondSlimeXPos + slimeFrameRec.width * 4.0f < 0) // Check if second Slime is off the left side
    {
        secondSlimeXPos = screenWidth + 35; // Reset second Slime's position to the right side of the screen with an offset
    }
}

// Render Knight sprite
void Menu::render_knight(void)
{
    knightFrameCounter++;

    // Update Knight's animation frame
    if (knightFrameCounter >= (60 / knightFramesSpeed))
    {
        knightFrameCounter = 0;
        knightCurrentFrame++;

        if (knightCurrentFrame > 8)
        {
            knightCurrentFrame = 0;
            knightSwitchSide = !knightSwitchSide; // Switch animation side
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

    // Flip the frame rectangle horizontally for correct rendering
    Rectangle knightFlippedFrameRec = knightFrameRec;
    knightFlippedFrameRec.width *= -1;

    // Draw the Knight sprite with texture rectangle adjustments
    DrawTexturePro(Knight, knightFlippedFrameRec, Rectangle{knightXPos, 330, knightFrameRec.width * 4.0f, knightFrameRec.height * 4.0f},
                   {knightFrameRec.width / 2, knightFrameRec.height / 2}, 0.0f, WHITE);
}

// Render the first Slime sprite
void Menu::render_slime(void)
{
    slimeFrameCounter++;

    // Update Slime's animation frame
    if (slimeFrameCounter >= (60 / slimeFramesSpeed))
    {
        slimeFrameCounter = 0;
        slimeCurrentFrame++;

        if (slimeCurrentFrame > 4)
            slimeCurrentFrame = 0;

        slimeFrameRec.x = (float)slimeCurrentFrame * (float)Slime.width / 4;
        slimeFrameRec.y = 1 * (float)Slime.height / 3;
    }

    // Flip the frame rectangle horizontally for correct rendering
    Rectangle slimeFlippedFrameRec = slimeFrameRec;
    slimeFlippedFrameRec.width *= -1;

    // Draw the first Slime sprite with texture rectangle adjustments
    DrawTexturePro(Slime, slimeFlippedFrameRec, Rectangle{slimeXPos, 343, slimeFrameRec.width * 4.0f, slimeFrameRec.height * 4.0f},
                   {slimeFrameRec.width / 2, slimeFrameRec.height / 2}, 0.0f, WHITE);
}

// Render the second Slime sprite behind the first one
void Menu::render_second_slime(void)
{
    // Flip the frame rectangle horizontally for correct rendering
    Rectangle slimeFlippedFrameRec = slimeFrameRec;
    slimeFlippedFrameRec.width *= -1;

    // Draw the second Slime sprite with texture rectangle adjustments
    DrawTexturePro(Slime, slimeFlippedFrameRec, Rectangle{secondSlimeXPos, 343, slimeFrameRec.width * 4.0f, slimeFrameRec.height * 4.0f},
                   {slimeFrameRec.width / 2, slimeFrameRec.height / 2}, 0.0f, WHITE);
}

// Return the current menu option
MenuOptions Menu::getOptions(void)
{
    return menu_options;
}
