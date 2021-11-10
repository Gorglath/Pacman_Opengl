#include "CubesSorter.h"

//Sort a given list of cubes by type.
void CubeSorter::sortCubes(vector<Cube>& cubes)
{
    for(auto& cube:cubes) 
    {
        CubeType c_Type = cube.GetCubeType();
        if(c_Type == CubeType::FOOD || c_Type == CubeType::PFOOD)
        {
            m_food_cubes.push_back(cube);
        }
        else if(c_Type == CubeType::GHOST)
        {
            m_ghosts_cubes.push_back(cube);
        }
        else if(c_Type == CubeType::PACMAN)
        {
            m_pacman_cube = cube;
        }
        else if(c_Type == CubeType::WALL)
        {
            m_wall_cubes.push_back(cube);
        }
        else if(c_Type == CubeType::Spawner)
        {
            m_food_cubes.push_back(cube);
            m_spawn_Position = cube.getTilePos();
        }
    }
    
}