#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <SDL.h>

#include <memory>
#include <vector>
#include "Shader.h"

#include "../game/Grid.h"
#include "../game/Cube.h"
#include "../game/FoodManager.h"
#include "../game/MazeManager.h"
#include "../game/PacmanManager.h"
#include "../game/GhostManager.h"
#include "../game/InputManager.h"
#include "../game/ScoreManager.h"
#include "../game/AStar.h"
#include "../game/SoundManager.h"
#include "../game/TextManager.h"
using std::vector;

// This game class runs a simple game loop
class Game {
   public:
    Game();
    virtual ~Game();

    void init(int screenWidth, int screenHeight);
    void load(bool reload);
    void update(float dt);
    void render();
    void clean();

    bool isRunning;
    int windowWidth, windowHeight;

   private:

    void setShaders();
    void restartGame();
    GLuint vao;
    GLuint buffer;
    int m_current_Loop_Number{0};
    float timeSinceStart;
    float m_time_To_Stay_Inverted {10.0f};
    float m_inverted_Timer{0.0f};
    float m_sound_Stop_Timer{0.0f};
    bool m_inverted{false};
    bool m_playing_Eat_Sound{false};
    bool m_already_Played_Opening_Sound{false};

    Matrix4 transform;
    Matrix4 projection;
    Matrix4 view;

    FoodManager m_foodmanager;
    MazeManager m_mazeManager;
    GhostManager m_ghostmanager;
    PacmanManager m_pacmanmanager;

    ScoreManager m_scoremanager;
    PathFinding m_pathFinding;
    InputManager m_inputManager;
    SoundManager m_soundManager;
    TextManager m_text_Manager;

    Shader m_cube_Shader;
    Shader m_text_Shader;
    Grid m_grid;
};

#endif
