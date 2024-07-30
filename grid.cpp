#include "grid.h"

Grid::Grid() {}

Grid::~Grid()
{
    UnloadMap(map);
}

void Grid::render(void)
{
    DrawTiled(map, 0, 0, WHITE);
}
