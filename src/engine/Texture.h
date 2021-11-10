#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool load(const string& filenameP);
	void updateInfo(int& widthOut, int& heightOut);
	void use() const;

	unsigned int getTextureID() const { return textureId; }
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	unsigned int textureId;
	string filename;
	int width;
	int height;
};

#endif
