#ifndef IMAGE_FORMAT_LOOKUP_H
#define IMAGE_FORMAT_LOOKUP_H


#include<GLFW/glfw3.h>
#include<string.h>

class FormatLookup {
public:
	const char* name;
	int value;
	int addrForName(const char *name);
};



static FormatLookup ImgFormTable[] = {
	{"RGB",	 GL_RGB},
	{"RGBA", GL_RGBA},
};

#endif // !IMAGE_FORMAT_LOOKUP_H

