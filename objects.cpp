#include "objects.h"
#include <iostream>

Objects::Objects()
{
    std::ifstream file("maps.json");

    data = json::parse(file);

    file.close();
}

void Objects::GetWorldObjects()
{
    Rectangle rect;

    try
    {
        std::cout << data["objects"] << std::endl;

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

                        std::cout
                            << "Object height: " << height << std::endl;
                        std::cout << "Object width: " << width << std::endl;
                        std::cout << "Object x: " << x << std::endl;
                        std::cout << "Object y: " << y << std::endl;
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