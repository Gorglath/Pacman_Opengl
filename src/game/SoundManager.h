#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Sound.h"
#include <map>
#include <string>
class SoundManager
{
    public:
    SoundManager() = default;
    ~SoundManager() = default;

    void loadSounds();
    void playSound(const char* name, int channel,bool override);
    void stopSound(int channel);

    inline bool getIsPlaying(int channel) const {return Mix_Playing(channel);} 
    private:
    std::string m_sounds_Folder_path = "../assets/Sounds/";
    std::map<std::string,Sound> m_gameSounds = 
    {
        {"pacman_beginning",Sound()},
        {"pacman_chomp",Sound()},
        {"pacman_death",Sound()},
        {"pacman_eatghost",Sound()},
        {"pacman_intermission",Sound()}
    };
};

#endif