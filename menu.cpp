#include "menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define BUTTON_WIDTH 240
#define BUTTON_HEIGHT 60

// Constructor for the Menu class
Menu::Menu()
{
    menu_options = INIT;   // Initialize menu options
    show_controls = false; // Initialize show_controls flag
    music_enabled = true;  // Initialize music enabled flag

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

    // Draw Knight and Slime animations
    update_positions();    // Update the positions of all moving sprites
    render_knight();       // Render Knight sprite
    render_slime();        // Render the first Slime sprite
    render_second_slime(); // Render the second Slime sprite behind the first one

    // Draw title text with a shadow effect
    if (!show_controls)
    {
        DrawTextEx(GetFontDefault(), "THIS IS A GAME", (Vector2){((float)screenWidth / 2) - 195, 85}, 50, 2, DARKGREEN);
        DrawTextEx(GetFontDefault(), "THIS IS A GAME", (Vector2){((float)screenWidth / 2) - 190, 80}, 50, 2, GREEN);

        // Draw a separator line between buttons
        DrawLine((float)screenWidth / 2 - 150, 140, (float)screenWidth / 2 + 150, 140, DARKGRAY);

        // Draw buttons with updated styles and larger text
        if (GuiButton((Rectangle){((float)screenWidth / 2) - 120, 150, BUTTON_WIDTH, BUTTON_HEIGHT}, "Start Game"))
        {
            menu_options = START_GAME; // Set menu option to start game if "Start Game" button is clicked
        }

        if (GuiButton((Rectangle){((float)screenWidth / 2) - 120, 220, BUTTON_WIDTH, BUTTON_HEIGHT}, "Show Controls"))
        {
            show_controls = true; // Show controls
        }

        if (GuiButton((Rectangle){((float)screenWidth / 2) - 120, 290, BUTTON_WIDTH, BUTTON_HEIGHT}, "Quit"))
        {
            menu_options = QUIT; // Set menu option to quit if "Quit" button is clicked
        }
    }
    else
    {
        // Display controls
        display_controls(); // Display controls if the flag is set

        // Draw the Back to Menu button
        if (GuiButton((Rectangle){((float)screenWidth / 2) - 120, (float)screenHeight - 100, BUTTON_WIDTH, BUTTON_HEIGHT}, "Back to Menu"))
        {
            show_controls = false; // Hide controls and return to menu
        }
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

void Menu::setOptions(MenuOptions setMenu)
{

    menu_options = setMenu;
}

// Display controls for movement and attack
void Menu::display_controls(void)
{
    const char *controlText =
        "Controls:\n"
        "W - Move Up\n"
        "S - Move Down\n"
        "A - Move Left\n"
        "D - Move Right\n"
        "Left Mouse Button - Attack\n"
        "M - Toggle Music";

    // Draw control text in the center of the screen
    DrawTextEx(GetFontDefault(), controlText, (Vector2){(float)screenWidth / 2 - 150, (float)screenHeight / 2 - 100}, 20, 2, WHITE);
}

// Return the current menu option
MenuOptions Menu::getOptions(void)
{
    return menu_options;
}

// Handle input for toggling controls display and music
