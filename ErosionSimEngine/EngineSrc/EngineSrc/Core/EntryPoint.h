/* ========================================================================
   $File: EntryPoint.h$
   $Date: 3/22/2021$
   $Revision: 2$
   $Creator: Brian Montgomery $
   $Notice: (C) Copyright 2021 by Monty, Inc. All Rights Reserved. $
   ======================================================================== */

#pragma once

#include "ErosionSimPCH.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//#define static "local_persist"
#define internal static
#define global_variable static
#define local_variable static

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int WinMain()
{
	//initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //specifies the primary (3.) opengl version you'll be using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //specifies the secondary (.3) opengl version you'll be using
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//sets the glfw profile

	//check if on mac and do whatis necessary to fix issues
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//creatingthe window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); //creates a window
	//error checking for the window creation
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); //stops glfw
		return -1;
	}

	glfwMakeContextCurrent(window); //makes the window the focus of the GLFWcontext

	glViewport(0, 0, 800, 600); //sets the openGL viewport

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //registers the screen resizing functionforusein resizing

	//set the normalized coords of the triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VBO; //creates a vertex buffer object
	glGenBuffers(1, &VBO); //creates a buffer using the unsigned int we created in the last line

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //binds this buffer to the array buffer layer

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //edits on information found in the currently bound array buffer






	//render loop
	while (!glfwWindowShouldClose(window)) //checks whether the window has been instructed to close
	{
		processInput(window); //processes input to the escape Key

		//render zone
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //state setting as to what the clear-tocolor should be
		glClear(GL_COLOR_BUFFER_BIT); //state using function



		glfwSwapBuffers(window); //swaps the buffer to prevent flickering
		glfwPollEvents(); //checks for any activity from the user
	}

	glfwTerminate(); //closes glfw
	return 0;
}
		


//function which resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}