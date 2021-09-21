#include"TextureClass.h"


Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType) {
	// Variables
	std::string imgFormat;
	const char* imgFormatPtr;
	GLenum format = 0;
	ID = 0;
	type = texType;

	auto in = OIIO::ImageInput::open(image);
	if (!in) {
		std::cout << "CANT OPEN " << image << std::endl;
		exit(1);
	}
	const OIIO::ImageSpec& spec = in->spec();
	GLsizei xres = spec.width;
	GLsizei yres = spec.height;
	GLsizei channels = spec.nchannels;
		// Debugging spec	
			//spec.channelformats;
			//std::cout << "spec: " << spec.pixel_bytes() << std::endl;
			//std::cout << "spec: " << spec.channel_bytes() << std::endl;
			//std::cout << "sizeof(spec.channelnames): " << sizeof(spec.channelnames) << std::endl;
			//std::cout << "spec.format : " << spec.format << std::endl;
			//std::cout << "spec.image_bytes: " << spec.image_bytes() << std::endl;
			//std::cout << "spec.nchannels : " << spec.nchannels << std::endl;
			//std::cout << "xres: " << xres << std::endl;
			//std::cout << "yres: " << yres << std::endl;
	
	std::vector<unsigned char> pixels(spec.image_bytes());
	int scanlinesize = spec.width * spec.nchannels * sizeof(pixels[0]);
	int xstride = spec.format * spec.nchannels;
	//int ystride = xstride * spec.width * -1;
	//int zstride = ystride * spec.height * -1;
	int ystride = xstride * spec.width;
	int zstride = ystride * spec.height;

	for (int i = 0; i < spec.nchannels; i++) {
		//std::cout << i << ": " << spec.channelnames[i] << std::endl;
		imgFormat.append(spec.channelnames[i]);
	}
	//std::cout << imgFormat << std::endl;
	imgFormatPtr = &imgFormat[0];
	format = ImgFormTable->addrForName(imgFormatPtr);
	//std::cout << "format: " << format << std::endl;

	 //in->read_image(OIIO::TypeDesc::UINT8, &pixels[0], xstride, -1 * ystride, zstride);
	in->read_image(OIIO::TypeDesc::UINT8, &pixels[0] + (yres - 1) * ystride, xstride, -ystride);
	in->close();
	
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);


	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// For: snatti89_sunset1.png: glTexImage2D(texType, 0, GL_RGBA, xres, yres, 0, format, pixelType, &pixels[0]);
	glTexImage2D(texType, 0, GL_RGBA, xres, yres, 0, format, pixelType, &pixels[0]);
	
	
	glGenerateMipmap(texType);


	//stbi_image_free(bytes);
	 
	glBindTexture(texType, 0);
}

void Texture::uniTex(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}