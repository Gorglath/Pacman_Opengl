#ifndef GRID_H
#define GRID_H
#include "Cube.h"
#include "AStar.h"

#include <vector>
using std::vector;

class Grid
{
    public:
    Grid() = default;
    ~Grid() = default;
    
    vector<Cube> Init(PathFinding& aStar);
    private:
    vector<Cube> m_cubes;
};
#endif