#include "Grid.h"
#include "MazeTextParser.h"
#include "ObjectGenerator.h"

//Create cubes in a grid formation.
vector<Cube> Grid::Init(PathFinding& aStar)
{
    MazeTextParser parser;
    ObjectGenerator generator;
    
    //Parse the level text file.
    char* maze = parser.ParseMazeText();
    
    //Generate cubes based on given char array.
    m_cubes = generator.GenerateObjects(maze);

    //Initialize a* based on the given cubes.
    aStar.initPathfinding(22,28,m_cubes);
    return m_cubes;
}



