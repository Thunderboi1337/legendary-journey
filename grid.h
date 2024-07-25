#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>
#include "raylib.h"

class Grid
{
public:
    Grid();
    ~Grid();
    bool loadFromFile(const std::string &filename);
    void render(void);

private:
    int width, height;
    std::vector<std::vector<int>> map;
    Texture2D tilesetTexture;
    int tileSize;
};

#endif