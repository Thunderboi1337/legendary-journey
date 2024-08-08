#ifndef OBJECTS_H
#define OBJECTS_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include "raylib.h"

using json = nlohmann::json;

class Objects
{
public:
    Objects();

    json data;

    void GetWorldObjects();
    void render(void);
    std::vector<Rectangle> rectangles;

    std::vector<Rectangle> GetObjects();
    bool isColliding(const Rectangle &rect);

    // Other methods like collision detection can be added here

private:
    int height;
    int width;
    int x;
    int y;
};

#endif