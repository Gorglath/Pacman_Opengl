#include <SDL.h>

#include <iostream>

#include "engine/Game.h"
#include "engine/Timer.h"
#include "engine/Window.h"

using std::cout;
using std::endl;

LogConfig LOG_CONFIG = {};

int main(int argc = 0, char **argv = nullptr) {
    if (argc > 0) {
        for (int i = 0; i < argc; ++i) {
            cout << argv[i] << endl;
        }
    }

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 640;

    // Init logging
    LOG_CONFIG.reporting_level = Debug;
    LOG_CONFIG.restart = true;
    if (LOG_CONFIG.restart) {
        Log::restart();
    }

    // Init window
    Window window = Window("Pacman");
    if (!window.init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
        return 1;
    }

    // Init game
    Timer timer;
    Game game;
    game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.load(false);

	// Delta time in seconds
	float dt;

    // Game loop
    while (game.isRunning) {
        dt = static_cast<float>(timer.computeDeltaTime()) / 1000.0f;
        window.updateFpsCounter(dt);

        game.update(dt);

        window.clearBuffer();
        game.render();
        window.swapBuffer();

        // Delay frame if game runs too fast
        timer.delayTime();
    }

    // Exit game
    game.clean();
    window.clean();
    return 0;
}
