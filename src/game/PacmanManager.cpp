#include "PacmanManager.h"
void PacmanManager::setPacManCube(Cube& cube)
{
    //Set variables.
    m_pacman_Cube = cube;
    m_speed_X = 4.0f;
    m_speed_Y = 4.0f;
    m_move_Horizontal = false;
    m_move_Vertical = false;
    m_pacman_Initial_Position = m_pacman_Cube.getTilePos();
}

void PacmanManager::update(InputManager& inputManager,MazeManager& mazeManager,float dt)
{

        Vector2 offset { m_pacman_Cube.getTilePos() };
        int x = offset.x;
        int y = offset.y;
        bool is_In_Moving_Range = ((x - offset.x < 0.08f && x - offset.x > -0.08f) && (y - offset.y < 0.08f && y - offset.y > -0.08f));
        
        //Check if the ghost is on a grid position (or if pacman is static). 
        if(is_In_Moving_Range || (!m_move_Horizontal && !m_move_Vertical))
        {
            checkInput(inputManager,mazeManager);
        }
        
        //Move according to the input detected.
        if(m_move_Horizontal)
        {
            offset.x += m_speed_X * dt;
            m_pacman_Cube.setTilePos(offset);
        }
        else if(m_move_Vertical)
        {
            offset.y += m_speed_Y * dt;
            m_pacman_Cube.setTilePos(offset);
        }

        //Check if pacman is out of grid bounds.
        checkBounds();

        //Apply translation.
        Matrix4 basePosition = Matrix4::createTranslation(Vector3(offset.x, offset.y, -30.0f));

        m_pacman_Cube.setTransform(basePosition);
}

//Check if pacman can move in the given direction.
bool PacmanManager::checkIfCanMoveInDirection(Direction direction,MazeManager& mazeManager)
{
    Vector3 move_Direction;
    Vector3 pacman_Position = m_pacman_Cube.getTranslation();
    switch (direction)
    {
    case Direction::UP:
        move_Direction = Vector3(0,(m_speed_Y > 0)? m_speed_Y : m_speed_Y * -1,0);
        break;
    case Direction::DOWN:
        move_Direction = Vector3(0,(m_speed_Y < 0)? m_speed_Y : m_speed_Y * -1,0);
        break;
    case Direction::LEFT:
        move_Direction = Vector3((m_speed_X < 0)? m_speed_X : m_speed_X * -1,0,0);
        break;
    case Direction::RIGHT:
        move_Direction = Vector3((m_speed_X > 0)? m_speed_X : m_speed_X * -1,0,0);
        break;
    default:
        break;
    }
    return !mazeManager.getIsCollidingWithWall(move_Direction,pacman_Position,0.99f,1.3f);
}
//Check if pacman reached a wall.
void PacmanManager::checkIfReachedWall(MazeManager& mazeManager)
{
        Vector3 pacman_position = m_pacman_Cube.getTranslation();
        if(mazeManager.getIsCollidingWithWall(m_pacman_direction,pacman_position,0.9f,1.3f))
        {
            m_move_Vertical = false;
            m_move_Horizontal = false;
        }
}

void PacmanManager::checkBounds()
{
    Vector2 pos = m_pacman_Cube.getTilePos(); 
    if(pos.x < 0)
    {
        pos.x = 20;
        m_pacman_Cube.setTilePos(pos);
        m_move_Vertical = false;
    }
    else if(pos.x > 20)
    {
        pos.x = 0;
        m_pacman_Cube.setTilePos(pos);
        m_move_Vertical = false;
    }
}
//Set the move direction based on the player input.
void PacmanManager::checkInput(InputManager& inputManager,MazeManager& mazeManager)
{
    //Check the player input for each direction.
        if(inputManager.getMoveDown())
        {
            //Check if pacman is not already moving in that direction.
            if(m_current_Direction != Direction::DOWN)
            {
                //Check if it is possible to move in that direction.
                if(checkIfCanMoveInDirection(Direction::DOWN,mazeManager))
                {
                    m_current_Direction = Direction::DOWN;

                    m_move_Vertical = true;
                    m_move_Horizontal = false;
                    m_speed_Y = (m_speed_Y < 0) ? m_speed_Y : m_speed_Y * -1;
                    m_pacman_direction = Vector3(0.0f,m_speed_Y,0.0f);
                }
            }
        }
        else if(inputManager.getMoveUp())
        {
            if(m_current_Direction != Direction::UP)
            {
                if(checkIfCanMoveInDirection(Direction::UP,mazeManager))
                {
                    m_current_Direction = Direction::UP;
    
                    m_move_Vertical = true;
                    m_move_Horizontal = false;
                    m_speed_Y = (m_speed_Y > 0) ? m_speed_Y : m_speed_Y * -1;
                    m_pacman_direction = Vector3(0.0f,m_speed_Y,0.0f);
                }
            }
        }
        if(inputManager.getMoveLeft())
        {
            if(m_current_Direction != Direction::LEFT)
            {
                if(checkIfCanMoveInDirection(Direction::LEFT,mazeManager))
                {
                    m_current_Direction = Direction::LEFT;
                   
                    m_move_Vertical = false;
                    m_move_Horizontal = true;
                    m_speed_X = (m_speed_X < 0) ? m_speed_X : m_speed_X * -1;
                    m_pacman_direction = Vector3(m_speed_X,0.0f,0.0f);
                }
            }
        }
        else if(inputManager.getMoveRight())
        {
            if(m_current_Direction != Direction::RIGHT)
            {
                if(checkIfCanMoveInDirection(Direction::RIGHT,mazeManager))
                {
                    m_current_Direction = Direction::RIGHT;
    
                    m_move_Vertical = false;
                    m_move_Horizontal = true;
                    m_speed_X = (m_speed_X > 0) ? m_speed_X : m_speed_X * -1;
                    m_pacman_direction = Vector3(m_speed_X,0.0f,0.0f);
                }
            }
        }
        checkIfReachedWall(mazeManager);
}
void PacmanManager::draw(Shader& shader)
{
    m_pacman_Cube.draw(shader);
}
//Returns pacman to his initial position.
void PacmanManager::resetPacman()
{
    m_current_Direction = Direction::STATIC;
    m_move_Vertical = false;
    m_move_Horizontal = false;
    m_pacman_Cube.setTilePos(m_pacman_Initial_Position);
}
void PacmanManager::clean()
{
    m_pacman_Cube.clean();
    m_current_Direction = Direction::STATIC;
}

void PacmanManager::setPacmanInverted(bool inverted)
{
    if(inverted)
    {
        m_speed_X = m_speed_X * 1.2f;
        m_speed_Y = m_speed_Y * 1.2f;
    }
    else
    {
        m_speed_X = m_speed_X / 1.2f;
        m_speed_Y = m_speed_Y / 1.2f;
    }
}