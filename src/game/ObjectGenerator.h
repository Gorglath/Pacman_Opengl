#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

#include "Cube.h"
#include <vector>
using std::vector;
class ObjectGenerator
{
    public:
    ObjectGenerator() = default;
    ~ObjectGenerator() = default;

    vector<Cube> GenerateObjects(char* maze);

    private:
    Cube CreateCube(Vector2& pos,float scale,const Color& color,CubeType type);

    Matrix4 ApplyMatrixes(Vector2& pos,float scale);
};
#endif