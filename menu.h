#ifndef MENU_H
#define MENU_H

#include "raylib.h"

enum MenuOptions
{
    INIT,
    START_GAME,
    MUSIC_TOGGLE,
    QUIT
};

class Menu
{
private:
public:
    Menu();
    ~Menu();
    Texture2D Knight;
    Texture2D Slime;

    MenuOptions menu_options;

    void render(void);
    void render_knight(void);
    void render_slime(void);
    MenuOptions getOptions(void);

    void update_positions(void);

    Rectangle frameRec;

    int screenHeight;
    int screenWidth;

    bool switch_side;

    bool knightSwitchSide;
    int knightFramesSpeed;
    int knightCurrentFrame;
    int knightFrameCounter;
    float knightXPos;
    float knightSpeed;
    Rectangle knightFrameRec;

    int slimeFramesSpeed;
    int slimeCurrentFrame;
    int slimeFrameCounter;
    float slimeXPos; // Initial X position of Slime
    float slimeSpeed;
    Rectangle slimeFrameRec;
};

#endif