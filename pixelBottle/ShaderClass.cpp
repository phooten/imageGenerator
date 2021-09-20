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
	//GLint compileStatus;
	//GLint linkStatus;

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");
	
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type) {
	// Variables
	const unsigned int logLen = 1024;
	GLint compileStatus;
	char infoLog[logLen];
	//GLchar* buffer = new GLchar[logLen];
	
	// Checks for compile vs linking
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			glGetShaderInfoLog(shader, logLen, NULL, infoLog);
			std::cout << "SHADER COMPILATION ERROR for: " << type << std::endl << infoLog << std::endl;
			//return false;
		} 
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE) {
			glGetProgramInfoLog(shader, logLen, NULL, infoLog);
			std::cout << "SHADER LINKING ERROR for: " << type << std::endl << infoLog << std::endl;
			//return false;
		}
	}

	
/*
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {

		GLint infoLogLength;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(vertexShader, infoLogLength, &bufferSize, buffer);

		std::cout << "Vertex Shader - Compile: " << std::endl << buffer << std::endl;

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
*/
	return;
}