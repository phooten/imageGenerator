/**
	Overview: Create a pixel image with random variations in color and object
	@file main.cpp
	@author Parker Hooten
	@version 1.1 9/15/2021 [ D/M/Y ]
	@credit: 
		-> Victor Gordan's "opengl-tutorials" on youtube and github.	link:https://github.com/VictorGordan/opengl-tutorials
				- Shadercode, Usage of GLFW/glad functions, 
		-> Jamie King's	"3D Computer Graphics Using OpenGL" on youtube. link:https://www.youtube.com/watch?v=Dyue3MzJDss&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY&index=5
*/

/* 
	Psuedo Code Outline:

	 - create pixel map trueResolution = (width*(truePix) x height*(truePix)
			-> Want a high res .jpg, so each pixel = truePix = len*len pixels
	 - fill background color
	 - fill in bottle with base color
		 - base color for cap
		 - base color for bottle
		 - base color for logo
	 - output final images
	 - shading

	Prereq: 
		- Linker -> input -> Add Additional Dependancies: glfw3.lib, opengl32.lib
		- C++ -> general -> Add Additional include Directories: GL, glad, GLFW, KHR
		- C++-> general -> Add Additional #using Directories: glfw3.lib
*/



// Jamie:	https://www.youtube.com/watch?v=6c1QYZAEP2M&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY
// Victor:  https://www.youtube.com/watch?v=YaiSvKTOeRg&list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-&index=6

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VertexBufferObjectClass.h"
#include"VertexArrayObjectClass.h"
#include"ElementBufferObjectClass.h"

int main() {
	// Variables
	int bloc = 20;								// Length and width of a bloc
	int windowWidth = bloc * 32;//11;			// Length and width of the composition based on units of bloc
	int windowHeight = bloc * 32;
	GLfloat colorList[4][4] = {
		{ 0.91f, 0.90f, 0.92f, 1.00f },		// 0 - white
		{ 0.94f, 0.94f, 0.71f, 1.00f },		// 1 - tan
		{ 0.85f, 0.76f, 0.82f, 1.00f },		// 2 - pink
		{ 0.46f, 0.85f, 0.80f, 1.00f }		// 3 - black
	};

	// Color selector variables
	int bottCS = 2;		// bottle 
	int bgCS = 1;		// background
	GLfloat bottColor[4] = { colorList[bottCS][0], colorList[bottCS][1], colorList[bottCS][2], colorList[bottCS][3] };
	GLfloat bgColor[4] =   { colorList[bgCS][0],   colorList[bgCS][1],	 colorList[bgCS][2],   colorList[bgCS][3]   };

	// Startup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat verts[] = {
		// Position					// Color R, G, B																

		//-0.75f, +0.75f, 0.0f,		1.0f, 0.0f, 0.0f, 						// Top Left			0
		//+0.75f, +0.75f,	0.0f,		1.0f, 0.0f, 0.0f, 						// Top Right		1
		//-0.75f, -0.75f,	0.0f,		1.0f, 0.0f, 0.0f, 						// Bottom Left		2
		//+0.75f, -0.75f,	0.0f,		1.0f, 0.0f, 0.0f, 						// Bottom Right		3

		//-0.75f, +0.75f, 0.0f,		bottColor[0], bottColor[1], bottColor[2], 						// Top Left			0
		//+0.75f, +0.75f,	0.0f,		bottColor[0], bottColor[1], bottColor[2], 						// Top Right		1
		//-0.75f, -0.75f,	0.0f,		bottColor[0], bottColor[1], bottColor[2], 						// Bottom Left		2
		//+0.75f, -0.75f,	0.0f,		bottColor[0], bottColor[1], bottColor[2], 						// Bottom Right		3
		

		-0.75f, +0.75f, 0.0f,		bottColor[0], bottColor[1], bottColor[2], 						// Top Left			0
		+0.75f, +0.75f,	0.0f,		bottColor[0], bottColor[1], bottColor[2], 						// Top Right		1
		-0.75f, -0.75f,	0.0f,		1.0f, 1.0f, 1.0f, 						// Bottom Left		2
		+0.75f, -0.75f,	0.0f,		1.0f, 1.0f, 1.0f, 						// Bottom Right		3
	};

	GLuint windingOrder[]{
		0,1,3,			// Right half triangle
		3,2,0			// Left half triangle
	};


	// Creates and Validates window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Hydroflask", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);
	

	// Shader Code
	Shader ShaderProgram("default.vert", "default.frag");

	//VBO
	VertexArrayObject VAO;
	VAO.Bind();

	VertexBufferObject VBO(verts, sizeof(verts));
	ElementBufferObject EBO(windingOrder, sizeof(windingOrder));

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO.Unbind();
	EBO.Unbind();
	VBO.Unbind();
	

	// Main GLFW Loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		ShaderProgram.Activate();
		
		VAO.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	ShaderProgram.Delete(); 
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}