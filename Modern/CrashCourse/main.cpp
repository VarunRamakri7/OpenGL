#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
	// Square coordinates
	-0.5f, -0.5f, 0.0f, // Lower left
	0.5f, -0.5f, 0.0f, // Lower right
	0.5f, 0.5f, 0.0f, // Upper right
	-0.5f, 0.5f, 0.0f // Upper left

	/* // Triangle coordinates
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Bottom center*/
};

// Indices for vertices order
GLuint indices[] =
{
	// Square indices
	0, 1, 3,
	3, 1, 2

	/* // Triangle indices
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle*/
};

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Tell GLFW we are using OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tell GLFW we are using the CORE profile

	GLFWwindow* window = glfwCreateWindow(800, 800, "MainWindow", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Introduce the window to current context
	gladLoadGL(); //Load GLAD to configure OpenGL
	glViewport(0, 0, 800, 800);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.frag", "default.vert");

	// Generates Vertex Array Object and binds it
	VAO vao1;
	vao1.Bind();

	VBO vbo1(vertices, sizeof(vertices)); // Generates Vertex Buffer Object and links it to vertices
	EBO ebo1(indices, sizeof(indices));	// Generates Element Buffer Object and links it to indices

	vao1.LinkVBO(vbo1, 0);	// Links VBO to VAO

	// Unbind all to prevent accidentally modifying them
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color to it

		shaderProgram.Activate(); // Tell OpenGL which Shader Program we want to use
		vao1.Bind(); // Bind the VAO so OpenGL knows to use it
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // Swap the back buffer with the front buffer
		glfwPollEvents(); // Take care of all GLFW events
	}

	// Delete all the objects we've created
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}