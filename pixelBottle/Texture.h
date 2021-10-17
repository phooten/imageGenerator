#ifndef TEXTURE_H
#define TEXTURE_H

#include <string.h>
#include<glad/glad.h>
#include<stb/stb_image.h>
#include<OpenImageIO/imageio.h>
#include"Shader.h"
#include"ImageFormatLookup.h"

class Texture {
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum pixelType);

	void uniTex(Shader& shader, const char* uniform, GLuint unit);
	void Bind(unsigned int slot = 0);		// If this isn't specified, it will initialize to 0
	void Unbind();
	void Delete();
};


#endif // !TEXTURE_H
