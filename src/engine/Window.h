#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SDL.h>
#include "Log.h"

#include <string>

class Window {
   public:
    Window(const std::string &title);
    ~Window();

    bool init(int xPos, int yPos, int width, int height, bool isFullscreen);
    void logGlParams();
    void updateFpsCounter(float dt);
    void clearBuffer();
    void swapBuffer();
    void clean();

   private:
    SDL_Window *window;
    SDL_GLContext context;
    const std::string &title;

    double previousSeconds;
    double currentSeconds;
    int frameCount;

    // Delete
    Window() = delete;
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
};

#endif
