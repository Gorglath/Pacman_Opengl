#include "MazeTextParser.h"
#include <iostream>
#include <string>
#include <fstream>

char* MazeTextParser::ParseMazeText()
{
    //Open the text file.
    FILE *f = fopen("../assets/maze.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    //Convert the text file to a char array.
    char *string = (char *)malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    string[fsize] = 0;

    //Returned the converted text file.
    return string;
}