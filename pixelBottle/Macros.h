#ifndef MACROS_H
#define MACROS_H



#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
				  x;\
				  ASSERT(GLLogCall(#x, __FILE__, __LINE__));
/*
Puropse:	clear prior errors before wrapping around gl function calls to help find errors.
* See references : Documents->notes.txt->References
*/
static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

/*
	Puropse:	Wrap around gl function calls to help find errors.
				* See references: Documents -> notes.txt -> References
*/
static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


#endif // !MACROS_H