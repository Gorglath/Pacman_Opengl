#include "Ghost.h"
#include <random>
void Ghost::init(MazeManager& mazeManager,float speed,int chasingChance)
{
    //Initialize variables.
    m_speed = speed;
    m_chasing_Chance = chasingChance;
    m_is_Active = false;
    m_base_Color = m_related_Cube.GetCubeColor();
    m_inverted_Color = LIGHTBLUE;
    m_ghost_Initial_Position = m_related_Cube.getTilePos();
    applyMatrixes(m_ghost_Initial_Position);
}
void Ghost::update(Vector2& pacmanPosition,PathFinding& pathFinder,MazeManager& mazeManager,float dt)
{
    //If the ghost is not active, return.
    if(!m_is_Active)
        return;

    Vector2 offset { m_related_Cube.getTilePos() };
    int x = offset.x;
    int y = offset.y;
    bool is_In_Moving_Range = ((x - offset.x < 0.1f && x - offset.x > -0.1f) && (y - offset.y < 0.1f && y - offset.y > -0.1f));
    
    //Check if the ghost is on a grid position. 
    if(is_In_Moving_Range )
    {   
        //Check if the current grid position is a new grid position.
        if(floor(offset.x) != floor(m_ghost_Last_Position.x) || floor(offset.y) != floor(m_ghost_Last_Position.y) || m_state == ChaseState::NONE)
        {
            m_ghost_Last_Position = offset;
            //Check if the ghost is at turning point (or without chase state).
            if(isAtTurningPoint(mazeManager) || m_state == ChaseState::NONE)
            {
                //Set the ghost current moving direction.
                setMovementDirection();
                m_ghost_Last_Position = m_related_Cube.getTilePos();
                //Check if the ghost supposed to run away from pacman.
                if(m_state == ChaseState::RUNAWAY)
                {
                    //TODO: make the ghost run away from pacman.
                    choseRandomDirection(mazeManager,pacmanPosition);
                }
                else
                {
                    //Chose a random chase state (to move close to pacman or to chose a random direction).
                    int r = rand() % 10;
                    if(r < m_chasing_Chance)
                    {
                        m_path = pathFinder.getPath(m_ghost_Last_Position,pacmanPosition);
                        if(m_path.size() > 0)
                        {
                            m_state = ChaseState::CHASE;
                        }
                        else
                        {
                            choseRandomDirection(mazeManager,pacmanPosition);
                            m_state = ChaseState::RANDOM;
                        }
                    }
                    else
                    {
                        choseRandomDirection(mazeManager,pacmanPosition);
                        m_state = ChaseState::RANDOM;
                    }
                }    
            }
        }
    }

    //Move according to the chase state.
    if(m_state == ChaseState::RANDOM || m_state == ChaseState::RUNAWAY)
    {
        moveAlongDirection(dt);
    }
    else if(m_state == ChaseState::CHASE)
    {
        moveAlongPath(dt);
    }

    //Check if you are out of bounds.
    checkBounds();
}
//Set the ghost current direction.
void Ghost::setMovementDirection()
{
    if(m_move_Direction.x > 0.1f)
    {
        m_direction_State = Direction::RIGHT;
    }
    else if(m_move_Direction.x < -0.1f)
    {
        m_direction_State = Direction::LEFT;
    }
    else if(m_move_Direction.y > 0.1f)
    {
        m_direction_State = Direction::UP;
    }
    else if(m_move_Direction.y < -0.1f)
    {
        m_direction_State = Direction::DOWN;
    }
    else
    {
        m_direction_State = Direction::STATIC;
    }

}
//Move along the current move direction.
void Ghost::moveAlongDirection(float dt)
{ 
    Vector2 ghostPosition = m_related_Cube.getTilePos();

    ghostPosition += (m_move_Direction * m_speed * dt);

    applyMatrixes(ghostPosition);

    m_related_Cube.setTilePos(ghostPosition);
    

}
//Apply the ghost transform.
void Ghost::applyMatrixes(Vector2& ghostPosition)
{
    Matrix4 basePosition = Matrix4::createTranslation(Vector3(ghostPosition.x, ghostPosition.y, -30.0f));

    m_related_Cube.setTransform(basePosition);
}
//Move along the path to pacman.
void Ghost::moveAlongPath(float dt)
{
    //As long as the path is still populated.
    if (m_path.size() > 0)
    {
        //Move in the direction of the current point.
        Vector2 currentPoint = m_path[0];
        Vector2 ghostPosition = m_related_Cube.getTilePos();
        bool reachedCurrentPoint = ((currentPoint.x - ghostPosition.x < 0.08f && currentPoint.x - ghostPosition.x > -0.08f)
         && (currentPoint.y - ghostPosition.y < 0.08f && currentPoint.y - ghostPosition.y > -0.08f));
        if(!reachedCurrentPoint)
        {
            m_move_Direction = (currentPoint - ghostPosition);

            m_move_Direction.normalize();

            ghostPosition += (m_move_Direction * m_speed * dt);
            
            applyMatrixes(ghostPosition);
            
            m_related_Cube.setTilePos(ghostPosition);
        }
        else
        {
            //Remove the current point from the path.
            m_path.erase(m_path.begin());
        }
    }
    else
    {
        //If the path is empty, put the ghost on the closest grid position and reset the chase state.
        m_state = ChaseState::NONE;
        Vector2 newTilePos = m_related_Cube.getTilePos();
        newTilePos.x = round(newTilePos.x);
        newTilePos.y = round(newTilePos.y);
        m_related_Cube.setTilePos(newTilePos);
    }
}
//Chose a random direction base on available turns.
void Ghost::choseRandomDirection(MazeManager& mazeManager,Vector2& pacmanPosition)
{
    //Set variables
    Vector3 position = m_related_Cube.getTranslation();
    Vector3 direction = Vector3(-1,0,0);
    bool isAbleToTurnLeft = false;
    float dotRequried = 0.9f;
    float distanceToCheck = 1.3f;

    //Check each direction for a wall (don't go back on your own tracks).
    if(m_direction_State != Direction::RIGHT)
    {
        isAbleToTurnLeft = !mazeManager.getIsCollidingWithWall(direction,position,dotRequried,distanceToCheck);
    }   
    direction.x = 1;
    bool isAbleToTurnRight = false;
    if(m_direction_State != Direction::LEFT)
    {
        isAbleToTurnRight = !mazeManager.getIsCollidingWithWall(direction,position,dotRequried,distanceToCheck);
    }
    direction.x = 0;
    direction.y = 1;
    bool isAbleToTurnUp = false;
    if(m_direction_State != Direction::DOWN)
    {
        isAbleToTurnUp = !mazeManager.getIsCollidingWithWall(direction,position,dotRequried,distanceToCheck);
    }
    direction.y = -1;
    bool isAbleToTurnDown = false;
    if(m_direction_State != Direction::UP)
    {
        isAbleToTurnDown = !mazeManager.getIsCollidingWithWall(direction,position,dotRequried,distanceToCheck);
    }

    //Pick a random direction.
    vector<bool> options = {isAbleToTurnUp,isAbleToTurnDown,isAbleToTurnRight,isAbleToTurnLeft};
    int r = rand()%options.size(); 
    int escapeLoop = 0;

    //If the choosen direction is not available, increment until you find an available one.
    while (!options[r])
    {
        escapeLoop++;
        r++;
        if(r >= options.size())
        {
            r = 0;
        }

        //If all four directions are not available, escape the loop and reset chase state.
        if(escapeLoop > options.size())
        {
            m_state = ChaseState::NONE;
            r = -1;
            break;
        }
    }

    //Set the move direction based on the choosen direction.
    if(r == 0)
    {
        m_move_Direction = Vector2(0,1);
    }
    else if(r == 1)
    {
        m_move_Direction = Vector2(0,-1);
    }
    else if(r == 2)
    {
        m_move_Direction = Vector2(1,0);
    }
    else if (r == 3)
    {
        m_move_Direction = Vector2(-1,0);
    }

    //Debug directions.
    // std::string debug = (isAbleToTurnUp)? "True":"False";
    // debug.append(" - ");
    // debug.append((isAbleToTurnDown)? "True":"False");
    // debug.append(" - ");
    // debug.append((isAbleToTurnRight)? "True":"False");
    // debug.append(" - ");
    // debug.append((isAbleToTurnLeft)? "True":"False");
    // LOG(Info) << debug;
}
//Check if the ghost is at a turning point.
bool Ghost::isAtTurningPoint(MazeManager& mazeManager)
{
    //Set variables.
    Vector3 position = m_related_Cube.getTranslation();
    float dotRequried = 0.999f;
    float distanceToCheck = 1.1f;

    //If the ghost is moving horizontal, check for vertical empty spaces.
    if(m_direction_State == Direction::LEFT || m_direction_State == Direction::RIGHT)
    {
        Vector3 upDirection = Vector3(0,1,0);
        Vector3 downDirection = Vector3(0,-1,0);
        if(!mazeManager.getIsCollidingWithWall(upDirection,position,dotRequried,distanceToCheck) 
        || !mazeManager.getIsCollidingWithWall(downDirection,position,dotRequried,distanceToCheck))
        {
            // LOG(Info) << "Turning!";
            return true;
        }
    }
    //If the ghost is moving vertical, check for horizontal empty spaces.
    else
    {
        Vector3 leftDirection = Vector3(-1,0,0);
        Vector3 rightDirection = Vector3(1,0,0);
        if(!mazeManager.getIsCollidingWithWall(leftDirection,position,dotRequried,distanceToCheck)
         || !mazeManager.getIsCollidingWithWall(rightDirection,position,dotRequried,distanceToCheck))
        {
            // LOG(Info) << "Turning!";
            return true;
        }
    }

    return false;
}
//Check if the ghost is out of the grid bounds.
void Ghost::checkBounds()
{
    Vector2 pos = m_related_Cube.getTilePos(); 
    if(pos.x < 0)
    {
        pos.x = 20;
        m_related_Cube.setTilePos(pos);
    }
    else if(pos.x > 20)
    {
        pos.x = 0;
        m_related_Cube.setTilePos(pos);
    }
}
void Ghost::setGhostInvert(bool invert)
{
    if(invert)
    {
        if(m_is_Active)
        {
            //Set variables
            m_is_Invert = true;
            m_related_Cube.ChangeColor(m_inverted_Color);
            m_state = ChaseState::RUNAWAY;
            Vector2 currentPosition = m_related_Cube.getTilePos();

            //Reset the ghost position to the closest point on the grid.
            currentPosition = Vector2(round(currentPosition.x),round(currentPosition.y));
            m_move_Direction = Vector2(round(m_move_Direction.x),round(m_move_Direction.y));
            m_related_Cube.setTilePos(currentPosition);
            // LOG(Info) << "Inverted!";
        }
    }
    else
    {
        // LOG(Info) << "Not inverted!";
        m_is_Invert = false;
        m_state = ChaseState::RANDOM;
        m_related_Cube.ChangeColor(m_base_Color);
    }
}
//Move the ghost to the position and activates it.
void Ghost::activateGhost(Vector2& spawnPosition)
{
    m_related_Cube.setTilePos(spawnPosition);
    moveAlongDirection(0);
    m_is_Active = true;
    m_state = ChaseState::NONE;
}
//Deactivate the ghost and return it to her initial position.
void Ghost::respawnGhost()
{
    m_is_Invert = false;
    m_related_Cube.setTilePos(m_ghost_Initial_Position);
    m_related_Cube.ChangeColor(m_base_Color);
    m_is_Active = false;
    m_state = ChaseState::NONE;
    applyMatrixes(m_ghost_Initial_Position);
}
void Ghost::draw(Shader& shader)
{
    m_related_Cube.draw(shader);
}
void Ghost::clean()
{
    m_related_Cube.clean();
}
