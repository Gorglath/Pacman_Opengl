#include "TextManager.h"

void TextManager::init()
{
    //Init ttf.
    TTF_Init();
    
    //Load used font.
    m_font = TTF_OpenFont("../assets/crackman.regular.ttf",50);
    
    //Init game texts.
    m_scoreTitle.initText(m_font,"SCORE",{255,255,255,255},0.1f,-0.8f,0.8f);
    
    m_scoreValue.initText(m_font,"0",{255,255,255,255},0.1f,-0.8f,0.7f);
    
    m_livesTitle.initText(m_font,"LIVES",{255,255,255,255},0.1f,0.8f,0.8f);

    m_livesValue.initText(m_font,"3",{255,255,255,255},0.1f,0.8f,0.7f);
}

void TextManager::setScoreText(const char* text)
{
    //Clean the previous texture and set the new text.
    m_scoreValue.clean();
    m_scoreValue.setText(m_font,(char*)text,{255,255,255,255});
}
void TextManager::setLivesText(const char* text)
{
    m_livesValue.clean();
    m_livesValue.setText(m_font,(char*)text,{255,255,255,255});
}
void TextManager::draw(Shader& shader)
{
    m_scoreTitle.draw(shader);
    m_scoreValue.draw(shader);
    m_livesTitle.draw(shader);
    m_livesValue.draw(shader);
}

void TextManager::clean()
{
    m_scoreTitle.clean();
    m_scoreValue.clean();
    m_livesTitle.clean();
    m_livesValue.clean();
    TTF_CloseFont(m_font);
}