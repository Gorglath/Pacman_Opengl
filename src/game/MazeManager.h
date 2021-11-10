#ifndef MAZEMANAGER_H
#define MAZEMANAGER_H

#include "Cube.h"
#include <vector>

using std::vector;

enum class Direction
{
    STATIC,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class MazeManager
{
    public:
    MazeManager() = default;
    ~MazeManager() = default;

    void setWallCubes(vector<Cube>& wall_Cubes);

    void draw(Shader& shader);

    bool getIsCollidingWithWall(Vector3& desired_direction,Vector3& pacman_Position, float dot_Required, float distance_To_Check);
    void clean();
    private:
    vector<Cube> m_wall_Cubes;
    
};

#endif