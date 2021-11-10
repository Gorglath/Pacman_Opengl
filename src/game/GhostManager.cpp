#include "GhostManager.h"

void GhostManager::setGhostCubes(MazeManager& mazeManager,vector<Cube>& ghost_Cubes,Vector2& ghost_Spawner,float ghostSummonIntervals)
{
    m_spawn_Location = ghost_Spawner;
    m_ghost_Summon_Interval = ghostSummonIntervals;
    m_number_Of_Summoned_Ghosts = 0;
    
    Ghost ghost;
    int chasingChance = 0;
    
    m_ghost_Objects = vector<Ghost>();
    for (size_t i = 0; i < ghost_Cubes.size(); i++)
    {
        chasingChance += 2;
        ghost.setRelatedCube(ghost_Cubes[i]);
        ghost.init(mazeManager,3.5f,chasingChance);
        m_ghost_Objects.push_back(ghost);
    }
}

void GhostManager::draw(Shader& shader)
{
    for(auto& ghost:m_ghost_Objects)
    {
        ghost.draw(shader);
    }
}
void GhostManager::setInvertState(bool invert)
{
    for(auto& ghost:m_ghost_Objects)
    {
        ghost.setGhostInvert(invert);
    }
}
void GhostManager::update(Vector2& pacmanPosition, MazeManager& mazeManager,PathFinding& pathFinder,float dt)
{
    for (auto& ghost : m_ghost_Objects)
    {
        if(ghost.getIsActive())
        {
            ghost.update(pacmanPosition,pathFinder,mazeManager,dt);
        }
    }
     
    if(m_number_Of_Summoned_Ghosts < 4)
    {
        m_timer += dt;
        if(m_timer > m_ghost_Summon_Interval)
        {
            m_timer = 0;
            m_number_Of_Summoned_Ghosts++;
            for (auto& ghost : m_ghost_Objects)
            {
                if(!ghost.getIsActive())
                {
                    ghost.activateGhost(m_spawn_Location);
                    break;
                }
            }
            
        }
    }
}
bool GhostManager::isCollidingGhost(Vector2& pacmanPosition)
{
    for (auto& ghost:m_ghost_Objects)
    {
        Vector2 ghostPosition = ghost.getRelatedCubePosition();
        if(checkGhostCollision(ghostPosition,pacmanPosition))
        {
            return true;
        }
    }
    return false;
}
bool GhostManager::tryToEatGhost(Vector2& pacmanPosition)
{
    for(auto& ghost:m_ghost_Objects)
    {
        Vector2 ghostPosition = ghost.getRelatedCubePosition();
        if(checkGhostCollision(ghostPosition,pacmanPosition) && ghost.getIsInverted())
        {
            ghost.respawnGhost();
            m_number_Of_Summoned_Ghosts--;
            m_timer = 0;
            return true;
        }
    }
    return false;
}
void GhostManager::respawnAllGhosts()
{
    for(auto& ghost:m_ghost_Objects)
    {
        ghost.respawnGhost();
    }
    m_timer = 0.0f;
    m_number_Of_Summoned_Ghosts = 0;
}
bool GhostManager::checkGhostCollision(Vector2& ghostPosition,Vector2& pacmanPosition)
{
    return (Vector2::distance(pacmanPosition,ghostPosition) < 0.5f);
}
void GhostManager::clean()
{
    for(auto& ghost:m_ghost_Objects)
    {
        ghost.clean();
    }
    m_timer = 0.0f;
    m_number_Of_Summoned_Ghosts = 0;
}