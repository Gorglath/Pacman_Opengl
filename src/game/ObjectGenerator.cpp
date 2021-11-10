#include "ObjectGenerator.h"
#include "CubeFactory.hpp"
vector<Cube> ObjectGenerator::GenerateObjects(char* maze)
{
    //Set variables.
    vector<Cube> cubes;
    cubes.reserve(28*22);
    Vector2 pos;
    char current_Char;
    int ghost_Number = 0;

    //Generate cubes in a grid formation.
    for (size_t i = 0; i < 28; i++)
    {
        for (size_t j = 0; j < 22; j++)
        {
            current_Char = maze[(i * 23) + j];
            pos = {j,i};
            if(current_Char == 'x')
            {
               cubes.push_back(CreateCube(pos,1.5f,BLUE,CubeType::WALL));
            }
            else if(current_Char == 'f')
            {
               cubes.push_back(CreateCube(pos,0.5f,WHITE,CubeType::FOOD));
            }
            else if(current_Char == 'p')
            {
                cubes.push_back(CreateCube(pos,0.75f,ORANGE,CubeType::PFOOD));
            }
            else if(current_Char == 'g')
            {   
                Color ghostcolor;
                if(ghost_Number == 0)
                {
                    ghostcolor = PURPLE;
                }
                else if(ghost_Number == 1)
                {
                    ghostcolor = GREEN;
                }
                else if(ghost_Number == 2)
                {
                    ghostcolor = RED;
                }
                else
                {
                    ghostcolor = ORANGE;
                }
                cubes.push_back(CreateCube(pos,1.25f,ghostcolor,CubeType::GHOST));
                ghost_Number++;
            }
            else if(current_Char == 'm')
            {
                cubes.push_back(CreateCube(pos,1.25f,YELLOW,CubeType::PACMAN));
            }
            else if(current_Char == 's')
            {
                cubes.push_back(CreateCube(pos,0.5f,WHITE,CubeType::Spawner));
            }
            else
            {
                cubes.push_back(CreateCube(pos,1.0f,WHITE,CubeType::NONE));
            }
        }
        
    }
    return cubes;
}

//Creates a cube.
Cube ObjectGenerator::CreateCube(Vector2& pos,float scale,const Color& color,CubeType type)
{
    Cube cube = CubeFactory::GenerateCube(pos,color,type);

    Matrix4 translation = ApplyMatrixes(pos,scale);
    
    cube.setTransform(translation);

    return cube;
}

//Apply the cube matrixes.
Matrix4 ObjectGenerator::ApplyMatrixes(Vector2& pos,float scale)
{
    Matrix4 basePosition = Matrix4::createTranslation(Vector3(pos.x,pos.y, -30.0f));
    Matrix4 mScale = Matrix4::createScale(scale);
    Matrix4 translation =basePosition * mScale; 

    return translation;
}