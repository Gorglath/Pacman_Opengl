#include "Sound.h"

void Sound::loadSound(const char* name)
{
    m_sound = Mix_LoadWAV(name);
}
void Sound::playSound(int channel,bool override)
{
    if(!Mix_Playing(channel) && !override)
    {
        Mix_PlayChannel(channel,m_sound,0);
    }
    else if(override)
    {
        Mix_HaltChannel(channel);
        Mix_PlayChannel(channel,m_sound,0);
    }
}