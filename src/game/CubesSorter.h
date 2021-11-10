#ifndef CUBESORTER_H
#define CUBESORTER_H

#include "Cube.h"
#include <vector>

using std::vector;
class CubeSorter
{
    public:
    CubeSorter() = default;
    ~CubeSorter() = default;

    void sortCubes(vector<Cube>& cubes);

    inline vector<Cube> getFoodCubes() const {return m_food_cubes;}
    inline vector<Cube> getGhostCubes() const {return m_ghosts_cubes;}
    inline vector<Cube> getWallCubes() const {return m_wall_cubes;}
    inline Cube getPacmanCube() const {return m_pacman_cube;}
    inline Vector2 getSpawnLocation() const {return m_spawn_Position;}

    private:

    vector<Cube> m_food_cubes;
    vector<Cube> m_ghosts_cubes;
    vector<Cube> m_wall_cubes;
    Cube m_pacman_cube; 
    Vector2 m_spawn_Position;
};

#endif