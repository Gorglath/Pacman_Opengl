#ifndef FOODMANAGER_H
#define FOODMANAGER_H

#include "Cube.h"
#include <vector>

using std::vector;
class FoodManager
{
    public:

    FoodManager() = default;
    ~FoodManager() = default;

    void setFoodCubes(vector<Cube>& food_Cubes);

    void draw(Shader& shader);

    bool isEating(Vector3& pacman_Position);

    void setDidAtePowerFood(bool value){m_did_Ate_Power_Food = value;}
    inline bool getDidAtePowerFood() const {return m_did_Ate_Power_Food;}
    inline bool getDidAteAllFood() const {return m_food_Cubes.size() <= 0;}
    void clean();
    private:
    vector<Cube> m_food_Cubes;
    bool m_did_Ate_Power_Food{false};
};
#endif