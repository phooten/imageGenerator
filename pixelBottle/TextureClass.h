#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <string.h>
#include<glad/glad.h>
#include<stb/stb_image.h>
#include<OpenImageIO/imageio.h>
#include"ShaderClass.h"
#include"ImageFormatLookup.h"

class Texture {
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);

	void uniTex(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};


#endif // !TEXTURE_CLASS_H
