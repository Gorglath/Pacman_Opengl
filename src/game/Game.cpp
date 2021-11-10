#include "../engine/Game.h"
#include "../engine/Texture.h"

#include "CubesSorter.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
Game::Game() : isRunning(true), windowWidth(0), windowHeight(0) {

}

Game::~Game() {}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    isRunning = true;
}
//Restart the game.
void Game::restartGame()
{
    //Get pacman current life.
    int life = m_pacmanmanager.getPacmanLifes();

    //Substract one and check if the game is over.
    life--;
    if(life <= 0)
    {
        //Clean everything and load from the beginning.
        clean();
        load(true);
    }
    else
    {
        //Clear input and reset scripts.
        m_inputManager.clearInput();
        m_pacmanmanager.setPacmanLife(life);
        m_pacmanmanager.resetPacman();
        m_ghostmanager.respawnAllGhosts();
    }
}
//Load the game.
void Game::load(bool reload) 
{
    std::srand((int) std::time(nullptr));
    glEnable(GL_TEXTURE_2D);

    //Check if you need to reload the game from the beginning.
    if(!reload)
    {
        // Setup OpenGL
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);


        // Setup shader
        shader.compileVertexShader();
        shader.compileFragmentShader();
        shader.createShaderProgram();

        // Setup 3D scene
        projection = Matrix4::createPerspectiveFOV(70.0f, windowWidth, windowHeight, 0.1f, 1000.0f);
        view = Matrix4::createTranslation(Vector3(-(21/2),-(27/2),1));

        //Setup shader matrixes.
        shader.use();
        shader.setMatrix4("proj_matrix", projection);
        shader.setMatrix4("view_matrix",view);
    }
    
    //Initialize and sort the cubes.
    vector<Cube> cubes = m_grid.Init(m_pathFinding);
    CubeSorter sorter;
    sorter.sortCubes(cubes);

    //Distribute the cubes for each manager.
    cubes = sorter.getFoodCubes();
    m_foodmanager.setFoodCubes(cubes);

    Cube cube = sorter.getPacmanCube();
    m_pacmanmanager.setPacManCube(cube);

    cubes = sorter.getWallCubes();
    m_mazeManager.setWallCubes(cubes);
    
    cubes = sorter.getGhostCubes();
    //Also pass the ghost manager the ghost spawn location.
    Vector2 v = sorter.getSpawnLocation();
    m_ghostmanager.setGhostCubes(m_mazeManager,cubes,v,2);

    //Load the game sounds.
    m_soundManager.loadSounds();
    m_soundManager.playSound("pacman_beginning",0,true);
}

void Game::update(float dt) 
{
    //Update dt.
    timeSinceStart += dt;
    const float t = timeSinceStart * 0.3f;
   
    //Handle input.
    m_inputManager.handleInput();
    isRunning = m_inputManager.getQuit();
   
    //Update pacman.
    m_pacmanmanager.update(m_inputManager,m_mazeManager,dt);
    
    //Get pacman position (3D and 2D).
    Vector3 pacman_Position = m_pacmanmanager.getPacmanPosition();
    Vector2 pacman_Tile_Position = m_pacmanmanager.getPacmanGridPosition();

    //Check if pacman is colliding with food.
    if(m_foodmanager.isEating(pacman_Position))
    {
        //Play eating sound and start eating sound timer.
        m_soundManager.playSound("pacman_chomp",-1,false);
        m_playing_Eat_Sound = true;

        //Check if the food pacman ate was a power food.
        if(m_foodmanager.getDidAtePowerFood())
        {
            //Add score.
            m_scoremanager.addScore(100);

            //Invert the ghosts.
            m_inverted = true;
            m_inverted_Timer = 0;
            m_ghostmanager.setInvertState(true);

            //Reset the ate food bool.
            m_foodmanager.setDidAtePowerFood(false);
        }
        else
        {
            m_sound_Stop_Timer = 0.0f;
            m_scoremanager.addScore(10);
        }

        //Check if the player won the level.
        if(m_foodmanager.getDidAteAllFood())
        {
            m_soundManager.playSound("pacman_intermission",0,true);
            SDL_Delay(5000);

            //Clean the scene and reload from the beginning.
            clean();
            load(false);
            return;
        }
    }
    //Check if an eating sound is currently playing.
    else if(m_playing_Eat_Sound)
    {
        //Deactivate the eating sound after 0.3 seconds of not eating food.
        m_sound_Stop_Timer += dt;
        if(m_sound_Stop_Timer >= 0.3f)
        {
            m_playing_Eat_Sound = false;
            m_soundManager.stopSound(-1);
        }
    }

    if(m_inverted)
    {
        //Deactivate interted state after x time.
        m_inverted_Timer += dt;
        if(m_inverted_Timer >= m_time_To_Stay_Inverted)
        {
            m_inverted = false;
            m_ghostmanager.setInvertState(false);
        }
    }

    //Check for pacman collision with ghosts.
    if(m_ghostmanager.isCollidingGhost(pacman_Tile_Position))
    {
        if(m_inverted)
        {
            //Check if the ghost is inverted 
            if(m_ghostmanager.tryToEatGhost(pacman_Tile_Position))
            {
                m_soundManager.playSound("pacman_eatghost",-1,true);
                m_scoremanager.addScore(250);
            }
            else
            {
                //Restart the game.
                m_soundManager.playSound("pacman_death",0,true);
                SDL_Delay(2500);
                restartGame();
                return;
            }
        }
        else
        {
            m_soundManager.playSound("pacman_death",0,true);
            SDL_Delay(2500);
            restartGame();
            return;
        }
    }

    //Update the ghosts.
    m_ghostmanager.update(pacman_Tile_Position,m_mazeManager,m_pathFinding,dt);
}

void Game::render() 
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
   
    m_foodmanager.draw(shader);
    m_mazeManager.draw(shader);
    m_pacmanmanager.draw(shader);
    m_ghostmanager.draw(shader);
}

void Game::clean() 
{   
    m_inputManager.clearInput();
    m_foodmanager.clean();
    m_mazeManager.clean();
    m_pacmanmanager.clean();
    m_ghostmanager.clean();
}
