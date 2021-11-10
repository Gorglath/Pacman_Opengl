#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
class Sound
{
    public:
    Sound() = default;
    ~Sound() = default;

    void playSound(int channel,bool override);
    void loadSound(const char* name);

    private:
    Mix_Chunk* m_sound;
};

#endif