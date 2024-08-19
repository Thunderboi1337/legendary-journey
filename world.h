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

    void render(void);
    void render_trees(void);

private:
    Texture2D tilesetTexture;
    int tileSize;
    Map map;
    Map trees;
};

#endif