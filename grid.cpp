#include <iostream>
#include "raylib.h"

#include "grid.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Grid::Grid() : width(0), height(0) {}

Grid::~Grid() {}

bool Grid::loadFromFile(const std::string &filename)
{
    Map map = LoadTiled("test.tmj");

    return true;
}

void Grid::render(void)
{
    if (tilesetTexture.id == 0)
    {
        return; // Texture not loaded
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int tileIndex = map[i][j];
            int tilesPerRow = tilesetTexture.width / tileSize;
            int tileX = (tileIndex % tilesPerRow) * tileSize;
            int tileY = (tileIndex / tilesPerRow) * tileSize;
            Rectangle sourceRect = {(float)tileX, (float)tileY, (float)tileSize, (float)tileSize};
            Rectangle destRect = {(float)(j * tileSize), (float)(i * tileSize), (float)tileSize, (float)tileSize};

            DrawTextureRec(tilesetTexture, sourceRect, (Vector2){destRect.x, destRect.y}, WHITE);
        }
    }
}
