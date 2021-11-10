#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "../engine/Log.h"
class ScoreManager
{
    public:
    ScoreManager() = default;
    ~ScoreManager() = default;

    void addScore(int value);
    private:
    int m_player_score{0};

};
#endif