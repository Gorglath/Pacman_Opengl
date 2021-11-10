#include "InputManager.h"
#include <SDL.h>
void InputManager::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) 
                {
                    m_running = false;
                }
                else if(event.key.keysym.sym == SDLK_UP)
                {
                    m_move_Up = true;
                    m_move_Left = false;
                    m_move_Right = false;
                    m_move_Down = false;
                }
                else if(event.key.keysym.sym == SDLK_DOWN)
                {
                    m_move_Down = true;
                    m_move_Left = false;
                    m_move_Right = false;
                    m_move_Up = false;
                }
                else if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    m_move_Right = true;
                    m_move_Left = false;
                    m_move_Up = false;
                    m_move_Down = false;
                }
                else if(event.key.keysym.sym == SDLK_LEFT)
                {
                    m_move_Left = true;
                    m_move_Right = false;
                    m_move_Up = false;
                    m_move_Down = false;
                }
                else if(event.key.keysym.sym == SDLK_SPACE) // TODO: Remove after debug.
                {
                    SDL_Delay(10000);
                }
                break;
            default:
                break;
        }
    }
}

void InputManager::clearInput()
{
    m_move_Down = false;
    m_move_Left = false;
    m_move_Right = false;
    m_move_Up = false;
}