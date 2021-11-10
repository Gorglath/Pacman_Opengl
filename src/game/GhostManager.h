#ifndef GHOSTMANAGER_H
#define GHOSTMANAGER_H

#include "Cube.h"
#include "Ghost.h"
#include "MazeManager.h"
#include "AStar.h"
#include <vector>

using std::vector;
class GhostManager
{
    public:
    GhostManager() = default;
    ~GhostManager() = default;

    void setGhostCubes(MazeManager& mazeManager,vector<Cube>& ghost_cubes,Vector2& ghost_Spawner, float ghostSummonIntervals);
    void setInvertState(bool invert);
    bool isCollidingGhost(Vector2& pacmanPosition);
    bool tryToEatGhost(Vector2& pacmanPosition);
    void respawnAllGhosts();
    void update(Vector2& pacmanPosition,MazeManager& mazeManager,PathFinding& pathFinder,float dt);
    void draw(Shader& shader);

    void clean();
    
    private:
    bool checkGhostCollision(Vector2& ghostPosition,Vector2& pacmanPosition);
    vector<Ghost> m_ghost_Objects;
    Vector2 m_spawn_Location;
    float m_ghost_Summon_Interval;
    float m_timer;
    int m_number_Of_Summoned_Ghosts;
};

#endif