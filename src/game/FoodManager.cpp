#include "FoodManager.h"

void FoodManager::setFoodCubes(vector<Cube>& food_Cubes)
{
    m_food_Cubes = food_Cubes;
}

void FoodManager::draw(Shader& shader)
{
    for(auto& cube:m_food_Cubes)
    {
        cube.draw(shader);
    }
}

void FoodManager::clean()
{
    for(auto& cube:m_food_Cubes)
    {
        cube.clean();
    }
}

//Check if pacman is colliding with food.
bool FoodManager::isEating(Vector3& pacman_Position)
{
    Vector3 pacman_To_Food;
    float distance_To_Pacman;
    //Go over the food and check if there is one close enough to pacman.
    for(size_t i = 0; i < m_food_Cubes.size(); ++i)
    {
        distance_To_Pacman = Vector3::distance(m_food_Cubes[i].getTranslation(),pacman_Position);
        if(distance_To_Pacman < 0.25f)
        {
            //Check if the food is power food.
            if(m_food_Cubes[i].GetCubeType() == CubeType::PFOOD)
            {
                m_did_Ate_Power_Food = true;
            }
            //Remove the food eaten from the cubes array.
            m_food_Cubes.erase(m_food_Cubes.begin() + i);
            return true;
        }
    }
    return false;
}