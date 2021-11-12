#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include "Text.h"
#include <SDL_ttf.h>
#include <vector>

using std::vector;
class TextManager
{
    public:
    TextManager() = default;
    ~TextManager() = default;

    void init();

    void draw(Shader& shader);

    void clean();

    void setScoreText(const char* text);
    void setLivesText(const char* text);

    private:
    Text m_scoreTitle;
    Text m_scoreValue;
    Text m_livesTitle;
    Text m_livesValue;
    vector<Text> m_texts;
    TTF_Font* m_font;
};

#endif