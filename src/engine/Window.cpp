#include "Window.h"
#include "GlDebug.hpp"

#include <iostream>

using std::cout;
using std::endl;

Window::Window(const std::string &title)
    : context(nullptr), title(title), previousSeconds(0), currentSeconds(0), frameCount(0) {}

Window::~Window() {
    SDL_Quit();
    LOG(Info) << "Bye :)";
}

bool Window::init(int xPos, int yPos, int width, int height, bool isFullscreen) {
    int flags = SDL_WINDOW_OPENGL;
    if (isFullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LOG(Error) << "SDL initialisation failed";
        LOG(Error) << SDL_GetError();
        return false;
    }

    LOG(Info) << "Subsystems initialised";

    // Sdl window
    window = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, flags);
    if (window) {
        LOG(Info) << "WindowSdl initialised";
    } else
        return false;

    // OpenGL context
    context = SDL_GL_CreateContext(window);
    if (context) {
        LOG(Info) << "OpenGL Context initialised";
    } else
        return false;

    // OpenGL setup
    glewExperimental = GL_TRUE;
    GLenum initGLEW(glewInit());
    if (initGLEW == GLEW_OK) {
        LOG(Info) << "GLEW initialised";
    } else
        return false;

    // Size of the viewport
    glViewport(0, 0, width, height);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // OpenGL error callback
    if (glDebugMessageControlARB != nullptr) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROCARB) debugGlErrorCallback, nullptr);
        GLuint unusedIds = 0;
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
    }

    // Enable cull face optimization
    glEnable(GL_CULL_FACE);         // Cull face
    glCullFace(GL_BACK);            // Cull back face
    glFrontFace(GL_CCW);             // GL_CCW for Counter Clock-Wise 

    // Window color
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    
    return true;
}

void Window::logGlParams() {
        GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char* names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };
    LOG(Info) << "-----------------------------";
    LOG(Info) << "GL Context Params:";
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++) {
        int v = 0;
        glGetIntegerv(params[i], &v);
        LOG(Info) << names[i] << " " << v;
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    LOG(Info) << names[10] << " " << v[0] << " " << v[1];
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    LOG(Info) << names[11] << " " << (unsigned int)s;
    LOG(Info) << "";
}


void Window::clearBuffer() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Window::swapBuffer() { SDL_GL_SwapWindow(window); }

void Window::clean() {
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
}

void Window::updateFpsCounter(float dt) {
    double elapsedSeconds;

    currentSeconds += dt;
    elapsedSeconds = currentSeconds - previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        char tmp[128];
        double fps = (double)frameCount / elapsedSeconds;
        sprintf_s(tmp, "%s @ fps: %.2f", title.c_str(), fps);
        SDL_SetWindowTitle(window, tmp);
        frameCount = 0;
    }
    frameCount++;
}
