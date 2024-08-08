#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

class Grid
{
public:
    Grid();
    ~Grid();

    Map map = LoadTiled("maps.json");

    void render(void);

private:
    Texture2D tilesetTexture;
    int tileSize;
};

#endif