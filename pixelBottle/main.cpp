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

#include<OpenImageIO/imageio.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>					//!!!!!!!!! tutorial 7, 4 minutes in

#include"Shader.h"
#include"Texture.h"
#include"VertexBufferObject.h"
#include"VertexArrayObject.h"
#include"ElementBufferObject.h"
#include"Macros.h"



// Color selector variables
int g_bottCS = 2;								// bottle 
int g_bgCS = 1;								// background
int g_x = 0;
const int g_colorCount = 4;
std::string g_colorNameList[g_colorCount] = {
	"white",
	"tan",
	"pink",
	"teal"
};

GLfloat g_colorList[g_colorCount][4] = {
	{ 0.91f, 0.90f, 0.92f, 1.00f },			// 0 - white
	{ 0.94f, 0.94f, 0.71f, 1.00f },			// 1 - tan
	{ 0.85f, 0.76f, 0.82f, 1.00f },			// 2 - pink
	{ 0.46f, 0.85f, 0.80f, 1.00f }			// 3 - blue
};

											/*

/*
   Keyboard Callback Routine: 'c' cycle through colors, 'q' or ESC quit,
   This routine is called every time a key is pressed on the keyboard
*/
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//std::cout << "key: " << key << std::endl;
	std::cout << "background color: " << g_colorNameList[g_x] << std::endl;
	std::cout << "g_x: " << g_x << std::endl;

	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_C:		// 'c' - cycle to next color
			if (g_x >= 3) { g_x = 0; } else { g_x++; }
			if (g_bgCS > 3) { g_bgCS = 0; } else { g_bgCS++; }

			break;

		case GLFW_KEY_E:		// q - quit
		case GLFW_KEY_ESCAPE:	// esc - quit
			exit(0);

		default:		// not a valid key -- just ignore it
			return;
		}
	}
}



int main() {
	// Variables
	int bloc = 20;								// Length and width of a bloc
	int windowWidth = bloc * 32;//11;			// Length and width of the composition based on units of bloc
	int windowHeight = bloc * 32;

	// Color selector variables
	//int bottCS = 2;								// bottle 
	//int bgCS = 1;								// background
	
	GLfloat bottColor[4] = { g_colorList[g_bottCS][0], g_colorList[g_bottCS][1], g_colorList[g_bottCS][2], g_colorList[g_bottCS][3] };
	GLfloat bgColor[4] =   { g_colorList[g_bgCS][0],   g_colorList[g_bgCS][1],	 g_colorList[g_bgCS][2],   g_colorList[g_bgCS][3]   };

	GLfloat vertex[] = {
		// Position					// Color R, G, B							  // Texture Coords							

		//-0.75f, +0.75f, 0.0f,		bottColor[0], bottColor[1], bottColor[2],		0.0f, 1.0f,		// Top Left			0
		//+0.75f, +0.75f, 0.0f,		bottColor[0], bottColor[1], bottColor[2],		1.0f, 1.0f,		// Top Right		1
		//-0.75f, -0.75f, 0.0f,		bottColor[0], bottColor[1], bottColor[2],		0.0f, 0.0f,		// Bottom Left		2
		//+0.75f, -0.75f, 0.0f,		bottColor[0], bottColor[1], bottColor[2],		1.0f, 0.0f		// Bottom Right		3
		
		-0.5f,  0.0f,  0.5f,		bottColor[0], bottColor[1], bottColor[2],		0.0f, 0.0f,		
		-0.5f,  0.0f, -0.5f,		bottColor[0], bottColor[1], bottColor[2],		5.0f, 0.0f,		
		 0.5f,  0.0f, -0.5f,		bottColor[0], bottColor[1], bottColor[2],		0.0f, 0.0f,		
		 0.5f,  0.0f,  0.5f,		bottColor[0], bottColor[1], bottColor[2],		5.0f, 0.0f,		
		 0.0f,  0.8f,  0.0f,		bottColor[0], bottColor[1], bottColor[2],		2.5f, 5.0f,		
		 
	
	};

	GLuint indices[]{
		//0, 1, 3,								// Right Half Triangle
		//0, 2, 3									// Left Half Triangle
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4, 
		3, 0, 4,
	};


	// Startup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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
	
	// Blending 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Shader Code
	Shader ShaderProgram("vertex.shader", "fragment.shader");
	GLuint uniScaleID = glGetUniformLocation(ShaderProgram.ID, "uScale");
	GLfloat uScale = 0.5f;


	
	//VBO
	VertexArrayObject VAO;
	VAO.Bind();

	VertexBufferObject VBO(vertex, sizeof(vertex));
	ElementBufferObject EBO(indices, sizeof(indices));

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	EBO.Unbind();
	VBO.Unbind();

	Texture Snatti("pixilatedWaterBottle.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
//	Texture Snatti("snatti89_sunset1.png", GL_TEXTURE_2D, GL_UNSIGNED_BYTE);
//	Texture Snatti("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

	Snatti.uniTex(ShaderProgram, "uTex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	// Main GLFW Loop
	while (!glfwWindowShouldClose(window)) {
		//glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
		glClearColor(g_colorList[g_x][0], g_colorList[g_x][1], g_colorList[g_x][2], g_colorList[g_x][3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSetKeyCallback(window, keyCallback);
		ShaderProgram.Activate();
		
		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = currentTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(windowWidth / windowHeight), 0.1f, 100.0f );
		
		int modelLoc = glGetUniformLocation(ShaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(ShaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(ShaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniScaleID, uScale);
		Snatti.Bind();
		VAO.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));	// Pre-3D coordinates
		GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0));
		GLCall(glfwSwapBuffers(window));
		GLCall(glfwPollEvents());
	}

	// Cleanup
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	Snatti.Delete();
	ShaderProgram.Delete(); 
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}