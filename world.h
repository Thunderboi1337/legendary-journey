#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

class World
{
public:
    World();
    ~World();

    Map map = LoadTiled("maps.json");

    void render(void);

private:
    Texture2D tilesetTexture;
    int tileSize;
};

#endif