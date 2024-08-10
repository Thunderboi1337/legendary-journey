#include "objects.h"
#include <iostream>

Objects::Objects(std::string file_name)
{
    std::ifstream file(file_name);

    data = json::parse(file);

    file.close();
}

Objects::~Objects()
{
}

void Objects::GetWorldObjects()
{
    Rectangle rect;

    try
    {
        if (data.contains("layers"))
        {
            for (const auto &layer : data["layers"])
            {
                if (layer.contains("objects"))
                {
                    for (const auto &object : layer["objects"])
                    {

                        rect.height = object["height"];
                        rect.width = object["width"];
                        rect.x = object["x"];
                        rect.y = object["y"];

                        rectangles.push_back(rect);
                    }
                }
            }
        }
    }
    catch (const nlohmann::json::exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}

void Objects::render(void)
{
    for (const auto &rect : rectangles)
    {
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);
    }
}

std::vector<Rectangle> Objects::GetObjects()
{

    return std::vector<Rectangle>(rectangles);
}

bool Objects::isColliding(const Rectangle &rect)
{
    for (const auto &objectRect : rectangles)
    {
        if (CheckCollisionRecs(rect, objectRect))
        {
            return true;
        }
    }
    return false;
}
