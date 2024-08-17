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

    MenuOptions menu_options;

    void render(void);
    MenuOptions getOptions(void);
};

#endif