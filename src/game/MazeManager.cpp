#include "MazeManager.h"

void MazeManager::setWallCubes(vector<Cube>& wall_Cubes)
{
    m_wall_Cubes = wall_Cubes;
}

void MazeManager::draw(Shader& shader)
{
    for(auto& cube:m_wall_Cubes)
    {
        cube.draw(shader);
    }
}

void MazeManager::clean()
{
    for(auto& cube:m_wall_Cubes)
    {
        cube.clean();
    }
}

//Returns true if there is a wall in the given direction.
bool MazeManager::getIsCollidingWithWall(Vector3& desired_Direction,Vector3& character_Position, float dot_Required, float distance_To_Check)
{
    //Set variables.
    Vector3 position_To_Wall;
    desired_Direction.normalize();
    float distance_To_Position;

    //Go over each wall.
    for(auto& cube:m_wall_Cubes)
    {
        position_To_Wall = (cube.getTranslation() - character_Position);

        position_To_Wall.normalize();
        float dot = Vector3::dot(position_To_Wall,desired_Direction);
        
        //Check if the wall is in the direction that the character is moving toward.
        if(dot > dot_Required)
        {   
            //Check if the wall is close enough to be considered a collision.
            distance_To_Position = Vector3::distance(cube.getTranslation(),character_Position);
            if(distance_To_Position < distance_To_Check)
            {
                return true;
            }
        }
    }

    return false;
}

