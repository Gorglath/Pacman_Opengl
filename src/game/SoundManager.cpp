#include "SoundManager.h"

void SoundManager::loadSounds()
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    for(auto& [key,val]:m_gameSounds)
    {
        std::string path = m_sounds_Folder_path;
        path.append(key);
        path.append(".wav");
        const char* c = path.c_str();
        val.loadSound(c);
    }
}

void SoundManager::playSound(const char* name, int channel,bool override = false)
{
    m_gameSounds.at(name).playSound(-1,override);
}
void SoundManager::stopSound(int channel)
{
    Mix_HaltChannel(channel);
}