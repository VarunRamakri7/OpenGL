#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
	// Square vertices
	 //     COORDINATES  /        COLORS      /  TexCoord	// 
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner

	 /* // Triangle vertices
	 //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     1.0f, 0.0f,  0.0f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.0f, 1.0f,  0.0f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.0f, 0.0f,  1.0f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.5f, 0.5f, 0.0f, // Left mid
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.0f, 0.5f, 0.5f, // Right mid
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.5f, 0.0f,  0.5f  // Bottom mid*/

};

// Indices for vertices order
GLuint indices[] =
{
	/// Square indices
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle

	/*// Triangle indices
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

	GLFWwindow* window = glfwCreateWindow(1000, 1000, "MainWindow", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Introduce the window to current context
	gladLoadGL(); //Load GLAD to configure OpenGL
	glViewport(0, 0, 1000, 1000);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.frag", "default.vert");

	// Generates Vertex Array Object and binds it
	VAO vao1;
	vao1.Bind();

	VBO vbo1(vertices, sizeof(vertices)); // Generates Vertex Buffer Object and links it to vertices
	EBO ebo1(indices, sizeof(indices));	// Generates Element Buffer Object and links it to indices

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0); // Links VBO to VAO (layout == 0)
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Links VBO to VAO (layout == 1)
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Links VBO to VAO (layout == 2)

	// Unbind all to prevent accidentally modifying them
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	GLuint unifID = glGetUniformLocation(shaderProgram.ID, "scale"); // Get scale uniform from vertex shader

	// Texture
	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color to it

		shaderProgram.Activate(); // Tell OpenGL which Shader Program we want to use

		glUniform1f(unifID, 0.5f); // Set scale uniform
		popCat.Bind();

		vao1.Bind(); // Bind the VAO so OpenGL knows to use it
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // Swap the back buffer with the front buffer
		glfwPollEvents(); // Take care of all GLFW events
	}

	// Delete all the objects we've created
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}