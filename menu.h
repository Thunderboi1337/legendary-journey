#ifndef MENU_H
#define MENU_H

#include "raylib.h"

// Enum to represent various menu options
enum MenuOptions
{
    INIT,         // Initial state
    START_GAME,   // Start the game
    MUSIC_TOGGLE, // Toggle music
    QUIT          // Quit the game
};

// Menu class definition
class Menu
{
public:
    // Constructor and Destructor
    Menu();
    ~Menu();

    // Methods to render elements and manage menu options
    void render(void);              // Main render function to draw all elements
    void render_knight(void);       // Render the Knight sprite
    void render_slime(void);        // Render the first Slime sprite
    void render_second_slime(void); // Render the second Slime sprite
    MenuOptions getOptions(void);   // Get the current menu option

private:
    // Private members
    Texture2D Knight; // Texture for the Knight sprite
    Texture2D Slime;  // Texture for the Slime sprite

    MenuOptions menu_options; // Current menu option

    void update_positions(void); // Update positions of sprites

    Rectangle frameRec; // General frame rectangle for sprites (if needed)

    int screenHeight; // Height of the screen
    int screenWidth;  // Width of the screen

    bool switch_side; // Flag to switch Knight's side

    // Knight animation variables
    bool knightSwitchSide;    // Flag to determine Knight's side
    int knightFramesSpeed;    // Speed of Knight's frame animation
    int knightCurrentFrame;   // Current frame of Knight's animation
    int knightFrameCounter;   // Counter to manage Knight's frame rate
    float knightXPos;         // X position of Knight sprite
    float knightSpeed;        // Speed of movement for Knight
    Rectangle knightFrameRec; // Frame rectangle for Knight sprite

    // Slime animation variables
    int slimeFramesSpeed;    // Speed of Slime's frame animation
    int slimeCurrentFrame;   // Current frame of Slime's animation
    int slimeFrameCounter;   // Counter to manage Slime's frame rate
    float slimeXPos;         // X position of the first Slime sprite
    float slimeSpeed;        // Speed of movement for Slime
    Rectangle slimeFrameRec; // Frame rectangle for Slime sprite

    // Second Slime position
    float secondSlimeXPos; // X position of the second Slime sprite
};

#endif // MENU_H
