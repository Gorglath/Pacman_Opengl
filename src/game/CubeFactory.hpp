#ifndef CUBEFACTORY_H
#define CUBEFACTORY_H

#include "Cube.h"
#include "../engine/Vector2.h"
class CubeFactory{

    public:
    CubeFactory() = default;
    ~CubeFactory() = default;

    //Generate a cube object.
    static Cube GenerateCube(Vector2& pos,const Color cubeColor, CubeType cType)
    {
        Cube cube {pos,cubeColor,cType};
        cube.load();
        return cube;
    }
};
#endif