#include "menu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define BUTTON_WIDTH 240
#define BUTTON_HEIGHT 60

Menu::Menu(/* args */)
{
    menu_options = INIT;
}

Menu::~Menu()
{
}

void Menu::render(void)
{

    int screenWidth = GetScreenWidth();
    int screenHeigth = GetScreenHeight();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (GuiButton((Rectangle){(screenWidth / 2) - 135, 150, BUTTON_WIDTH, BUTTON_HEIGHT}, "Start Game"))
    {
        menu_options = START_GAME;
    }
    if (GuiButton((Rectangle){(screenWidth / 2) - 135, 220, BUTTON_WIDTH, BUTTON_HEIGHT}, "Quit"))
    {
        menu_options = QUIT;
    }

    EndDrawing();
}

MenuOptions Menu::getOptions(void)
{
    return menu_options;
}
