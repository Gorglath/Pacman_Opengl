#include "Timer.h"
#include <algorithm>

Timer::Timer() : frameStart(0), lastFrame(0), frameTime(0)
{
}

Timer::~Timer()
{
}

unsigned int Timer::computeDeltaTime()
{
    frameStart = SDL_GetTicks();
    unsigned int dt = frameStart - lastFrame;
    dt = std::min(dt, MAX_DT);
    timeSinceStart += static_cast<float>(dt) / 1000.0f;
    lastFrame = frameStart;
	return dt;    // Clamp delta time
}

void Timer::delayTime()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < frameDelay) {
        SDL_Delay(frameDelay - frameTime);
    }
}

double Timer::timeSinceStart = 0.0f;
