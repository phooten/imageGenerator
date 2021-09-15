/**
	Overview: Create a pixel image with random variations in color and object
	@file main.cpp
	@author Parker Hooten
	@version 1.1 9/14/2021 [ D/M/Y ]
*/

/*!
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

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	// Variables
	int bloc = 20;							// Length and width of a bloc
	int windowWidth = bloc * 11;			// Length and width of the composition based on units of bloc
	int windowHeight = bloc * 32;
	
	int bottleColor[4] = { 0.85f, 0.76f, 0.82f, 1.00f };			// Pink
	float backgroundColor[4] = { 0.12f, 0.10f, 0.14f, 1.00f };		// Deep Purple
	
	int capColor[4] = { 0.08f, 0.08f, 0.08f, 1.00f };				// Black
	int logoColor[4] = { 0.91f, 0.90f, 0.92f, 1.00f };				// White
	
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


	// Main GLFW Loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		//glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();



	return 0;
}