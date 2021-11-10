#ifndef GHOST_H
#define GHOST_H

#include "Cube.h"
#include "AStar.h"
#include "MazeManager.h"
#include <vector>

using std::vector;

enum class ChaseState
{
    NONE,
    RANDOM,
    CHASE,
    RUNAWAY
};
class Ghost
{
    public:
    Ghost() = default;
    ~Ghost()= default;

    void update(Vector2& pacmanPosition,PathFinding& pathFinder,MazeManager& mazeManager,float dt);
    void init(MazeManager& mazeManager,float speed,int chasingChance);

    void setRelatedCube(Cube& cube) {m_related_Cube = cube;}
    void setGhostState(ChaseState state) {m_state = state;}
    void activateGhost(Vector2& pos);
    void respawnGhost();
    void setGhostInvert(bool invert);

    inline Vector2 getRelatedCubePosition() const {return m_related_Cube.getTilePos();}
    inline bool getIsActive() const {return m_is_Active;}
    inline bool getIsInverted() const {return m_is_Invert;}
    void draw(Shader& shader);

    void clean();
    private:
    
    void choseRandomDirection(MazeManager& mazeManager,Vector2& pacmanPosition);
    bool isAtTurningPoint(MazeManager& mazeManager);
    void moveAlongDirection(float dt);
    void moveAlongPath(float dt);
    void setMovementDirection();
    void checkBounds();
    void applyMatrixes(Vector2& ghostPosition);

    Vector2 m_move_Direction;
    Vector2 m_ghost_Last_Position;
    Vector2 m_ghost_Initial_Position;
    ChaseState m_state;
    vector<Vector2> m_path;
    Cube m_related_Cube;
    Color m_base_Color;
    Color m_inverted_Color;
    Direction m_direction_State;
    float m_speed;
    int m_chasing_Chance;
    bool m_is_Active;
    bool m_is_Invert;
};

#endif