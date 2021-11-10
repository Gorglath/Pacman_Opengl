#ifndef PACMANMANAGER_H
#define PACMANMANAGER_H

#include "InputManager.h"
#include "MazeManager.h"
#include "Cube.h"

class PacmanManager
{
    public:
    PacmanManager() = default;
    ~PacmanManager() = default;

    void setPacManCube(Cube& cube);
    void setPacmanLife(int value){m_pacman_lifes = value;}

    void update(InputManager& inputManager,MazeManager& mazeManager,float dt);
    
    void draw(Shader& shader);

    void clean();

    void resetPacman();

    void setPacmanInverted(bool inverted);
    
    inline Vector3 getPacmanDirection() const{return m_pacman_direction;}
    inline Vector3 getPacmanPosition() const {return m_pacman_Cube.getTranslation();}
    inline Vector2 getPacmanGridPosition() const {return m_pacman_Cube.getTilePos();}
    inline int getPacmanLifes() const {return m_pacman_lifes;}
    private:
    
    void checkInput(InputManager& inputManager,MazeManager& MazeManager);
    bool checkIfCanMoveInDirection(Direction direction,MazeManager& mazeManager);
    void checkIfReachedWall(MazeManager& MazeManager);
    void checkBounds();
    bool m_move_Vertical;
    bool m_move_Horizontal;
    float m_speed_X;
    float m_speed_Y;
    int m_pacman_lifes{3};
    Direction m_current_Direction;
    Cube m_pacman_Cube;
    Vector3 m_pacman_direction;
    Vector2 m_pacman_Initial_Position;
};

#endif