#ifndef GRID_H
#define GRID_H

#include "raylib.h"

class Grid
{

public:
    Grid();
    ~Grid();

    Vector2 World{100, 100};
    Texture2D tile;

    void render(void);

private:
};

Vector2 IsoConvert(Vector2 cartesian);

#endif
