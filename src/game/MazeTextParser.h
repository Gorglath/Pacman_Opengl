#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include "CubeFactory.hpp"
class MazeTextParser
{
    public:
        MazeTextParser() = default;
        ~MazeTextParser() = default;

        char* ParseMazeText();
        
};
#endif