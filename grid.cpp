#include <iostream>

#include "grid.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Grid::Grid() : width(0), height(0) {}

Grid::~Grid() {}

bool Grid::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    json j;
    try
    {
        file >> j;
    }
    catch (const json::exception &e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    }
    file.close();

    // Parse JSON data
    try
    {
        width = j.at("width").get<int>();
        height = j.at("height").get<int>();

        auto layers = j.at("layers");
        for (const auto &layer : layers)
        {
            if (layer.at("type") == "tilelayer")
            {
                auto data = layer.at("data");
                map.resize(height, std::vector<int>(width));
                for (int i = 0; i < height; ++i)
                {
                    for (int j = 0; j < width; ++j)
                    {
                        map[i][j] = data.at(i * width + j).get<int>();
                    }
                }
            }
        }

        // Load tileset texture
        auto tilesets = j.at("tilesets");
        if (!tilesets.empty())
        {
            auto tileset = tilesets[0];
            std::string imagePath = tileset.at("image").get<std::string>();
            tileSize = tileset.at("tilewidth").get<int>();
            tilesetTexture = LoadTexture(imagePath.c_str());
        }
        else
        {
            std::cerr << "No tilesets found in JSON file." << std::endl;
            return false;
        }
    }
    catch (const json::exception &e)
    {
        std::cerr << "JSON field error: " << e.what() << std::endl;
        return false;
    }

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
