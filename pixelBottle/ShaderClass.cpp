#include"ShaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint compileStatus;
	GLint linkStatus;

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	
	// Checks the shader compiling code
	//		This needs to be put in a function, but figure out how to ouput the file title.
	//-------------------------------------------------------------------------
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {

		GLint infoLogLength;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(vertexShader, infoLogLength, &bufferSize, buffer);

		std::cout << "Vertex Shader - Compile: "<< std::endl << buffer << std::endl;

		delete[] buffer;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {

		GLint infoLogLength;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(fragmentShader, infoLogLength, &bufferSize, buffer);

		std::cout << "Vertex Shader - Compile: " << std::endl << buffer << std::endl;

		delete[] buffer;
	}
	//-------------------------------------------------------------------------


	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// Checks the shader compiling code
	//		This needs to be put in a function, but figure out how to ouput the file title.
	//-------------------------------------------------------------------------
	glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {

		GLint infoLogLength;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(ID, infoLogLength, &bufferSize, buffer);

		std::cout << "Vertex Shader - Compile: " << std::endl << buffer << std::endl;

		delete[] buffer;
	}

	//-------------------------------------------------------------------------

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	/*
		Proposed function to combine checking compiling and linking

		5:10 into video(#17): 	https://www.youtube.com/watch?v=6ByZWqPzI70&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY&index=17

		bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType){
				GLint status;
				objectPropertyGetterFunc(objectID, statusType, &compileStatus);
				if (compileStatus != GL_TRUE) {

					GLint infoLogLength;
					objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
					GLchar* buffer = new GLchar[infoLogLength];

					GLsizei bufferSize;
					getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);

					std::cout << "Vertex Shader - Compile: "<< std::endl << buffer << std::endl;

					delete[] buffer;
				}

		}
	*/
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}