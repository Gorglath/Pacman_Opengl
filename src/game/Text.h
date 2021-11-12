#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>
#include <GL/glew.h>
#include "../engine/Shader.h"
#include "../engine/Matrix4.h"
#include "Color.h"
class Text
{
    public:

    Text() = default;
    ~Text() = default;
    
    void initText(TTF_Font* font,char* text, SDL_Color color,float size,float xPos, float yPos);
    void setText(TTF_Font* font, char* text, SDL_Color color);
    void draw(Shader& shader);
    void clean();
    inline GLuint getTextureID() const {return m_textureID;}
    private:
    GLuint m_textureID;
    float m_x {0.5f};
    float m_y {0.5f};
    float m_initial_Scale{0.2f};
    float m_scale_X {0.2f};
    float m_scale_Y {0.2f};
    uint32_t vao { 0 };
    uint32_t vbo { 0 };
    uint32_t texVbo {0};

    float vertices[18] = 
    {
       -0.5f, -0.5f,  0.0f,
        -0.5f, 0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
 
         0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };

    float texCoords[12]
    {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
};

#endif