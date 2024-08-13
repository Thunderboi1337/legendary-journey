#include "world.h"
#include <iostream>

World::World()
{
}

World::~World()
{
    UnloadMap(map);
    UnloadMap(trees);
}

void World::render(void)
{
    DrawTiled(map, 0, 0, WHITE);
}

void World::render_trees(void)
{

    DrawTiled(trees, 0, 0, WHITE);
}
