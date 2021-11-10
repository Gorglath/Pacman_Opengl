#include "Texture.h"
#include "Log.h"

#include <GL/glew.h>
#include <SDL_image.h>
#include <sstream>

Texture::Texture() : textureId(0), filename(""), width(0), height(0) {}

Texture::~Texture() {}

void Texture::unload() {
    glDeleteTextures(1, &textureId);
}

bool Texture::load(const string& filenameP) {
    filename = filenameP;
    // Load from file
    SDL_Surface* surf = IMG_Load(filename.c_str());
    if (!surf) {
        LOG(Error) << "Failed to load texture file " << filename;
        return false;
    }
    width = surf->w;
    height = surf->h;
    int format = 0;
    if (surf->format->format == SDL_PIXELFORMAT_RGB24) {
        format = GL_RGB;
    } else if (surf->format->format == SDL_PIXELFORMAT_RGBA32) {
        format = GL_RGBA;
    }

    // Generate texture
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
    SDL_FreeSurface(surf); // We no longer need the surface

    // Generate mipmaps for texture
    glGenerateMipmap(GL_TEXTURE_2D);
    // configure wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Enable linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    LOG(Info) << "Loaded texture " << filename;

    return true;
}

void Texture::updateInfo(int& widthOut, int& heightOut) {
    widthOut = width;
    heightOut = height;
}

void Texture::use() const { glBindTexture(GL_TEXTURE_2D, textureId); }
