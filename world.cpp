#include "world.h"
#include <iostream>

World::World()
{
}

World::~World()
{
    UnloadMap(map);
}

void World::render(void)
{
    DrawTiled(map, 0, 0, WHITE);
}
