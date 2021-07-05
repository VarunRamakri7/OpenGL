#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex shader source code
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment shader source code
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";

int main()
{
	glfwInit(); // Initialize GLFW

	// Tell GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tell GLFW we are using only the core profile

	// Vertices for Equilateral triangle
	GLfloat equilateralVertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper
	};
	
	// Vertices for right angle triangle
	GLfloat rightAngleVertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Lower left
		-0.5f, 0.5f, 0.0f, // Upper
		0.5f, -0.5f, 0.0f // Lower right
	};

	GLfloat squareNormalVertices[] =
	{
		-0.5f, -0.5f, 0.0f, // Lower left
		0.5f, -0.5f, 0.0f, // Lower right
		-0.5f, 0.5f, 0.0f, // Upper Left
		0.5f, 0.5f, 0.0f, // Upper right
		0.5f, 0.5f, 0.0f, // Upper right
		0.5f, -0.5f, 0.0f // Lower right
	};

	GLfloat squareLineLoopVertices[] =
	{
		-0.5f, -0.5f, // Lower left
		-0.5f, 0.5f, // Upper Left
		0.5f, 0.5f, // Upper right
		0.5f, -0.5f // Lower right
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Main Window", NULL, NULL); // Create window
	if (window == NULL) // Check if window creation failed
	{
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Introduce window into current context

	gladLoadGL(); // Load GLAD so that it configures OpenGL

	glViewport(0, 0, 800, 800); // Specify viewport of OpenGL (fromt bottom-left to top-right)

	// Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader); // Compile shader into machine code

	//Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); // Compile shader into machine code

	// Create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader); // Attach vertex shader to program
	glAttachShader(shaderProgram, fragmentShader); // Attach fragment shader to program
	glLinkProgram(shaderProgram); // Link all shaders together into the program

	// Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint VAO, VBO; // Create reference containers

	// Generate VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); // Make VAO the current object by binding it

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(equilateralVertices), equilateralVertices, GL_STATIC_DRAW); // Introduce vertices into VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(rightAngleVertices), rightAngleVertices, GL_STATIC_DRAW); // Introduce vertices into VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(squareNormalVertices), squareNormalVertices, GL_STATIC_DRAW); // Introduce vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareLineLoopVertices), squareLineLoopVertices, GL_STATIC_DRAW); // Introduce vertices into VBO

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glEnableVertexAttribArray(0); // Enable the VA so that OpenGL knows to use it

	// Bind VAO and VBO to 0 so that we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.07f, 0.13f, 0.17, 0.1f); // Set background color
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window); // Swap buffers

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17, 0.1f); // Set background color
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); // Specify shader program to use
		glBindVertexArray(VAO); // Bind VAO so that OpenGL knows to use it
		glDrawArrays(GL_LINE_LOOP, 0, 4); // Draw shape
		glfwSwapBuffers(window); // Swap buffers

		glfwPollEvents(); // Process all GLFW events
	}

	// Delete all objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}