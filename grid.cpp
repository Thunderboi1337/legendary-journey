#include <iostream>

#include "grid.h"

Grid::Grid()
{
    tile = LoadTexture("tile_000.png");
    if (tile.id == 0)
    {
        std::cerr << "Failed to load texture!" << std::endl;
    }
}

Grid::~Grid()
{
    UnloadTexture(tile);
}

void Grid::render(void)
{

    for (int y = 0; y < World.y; y++)
    {
        for (int x = 0; x < World.x; x++)
        {

            Vector2 position = {x * 32, y * 32};
            // Convert to isometric coordinates
            position = IsoConvert(position);
            DrawTexture(tile, position.x, position.y, WHITE);
        }
    }
}

Vector2 IsoConvert(Vector2 cartesian)
{
    Vector2 iso;
    iso.x = (cartesian.x - cartesian.y) * 0.5f;
    iso.y = (cartesian.x + cartesian.y) * 0.25f;
    return iso;
}