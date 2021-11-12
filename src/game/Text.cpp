#include "Text.h"

void Text::initText(TTF_Font* font,char* text, SDL_Color color,float size,float xPos, float yPos)
{
    //Set variables
    m_initial_Scale = size;
    m_x = xPos;
    m_y = yPos;
    
    //Set the text texture.
    setText(font,text,color);

    //Generate buffers.
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glGenBuffers(1,&texVbo);
    glBindBuffer(GL_ARRAY_BUFFER,texVbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(texCoords),texCoords,GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER,texVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1); 
}
void Text::setText(TTF_Font* font,char* text, SDL_Color color)
{
    //Create the text surface and generate the texture.
    SDL_Surface* surface = TTF_RenderText_Blended(font,text,color);
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    int format = GL_RGB;

    if(surface->format->BytesPerPixel == 4) {
    format = GL_RGBA;
    }
    
    double aspectRatio = (double)surface->w/surface->h;

    m_scale_X = m_initial_Scale*aspectRatio;
    m_scale_Y = m_initial_Scale;

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
void Text::draw(Shader& shader)
{
    shader.use();

    //Bind the buffers and texture.
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER,texVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindTexture(GL_TEXTURE_2D,m_textureID);

    //Set the matrixes.
    Matrix4 position = Matrix4::createTranslation(Vector3(m_x,m_y,0.0f));
    Matrix4 scale = Matrix4::createScale(m_scale_X,m_scale_Y,1.0f);
    Matrix4 translation = position * scale;
    
    shader.setInteger("image",0);
    shader.setMatrix4("mv_matrix", translation);

    //Draw quad for the texture.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
}

void Text::clean()
{
    glDeleteTextures(1,&m_textureID);
}