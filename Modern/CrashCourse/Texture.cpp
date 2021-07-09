#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType; // Assigns the type of the texture ot the texture object

	// Stores the width, height, and the number of color channels of the image
	int widthImg;
	int heightImg;
	int numColCh;
	stbi_set_flip_vertically_on_load(true); // Flips the image so it appears right side up
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0); // Reads the image from a file and stores it in bytes

	glGenTextures(1, &ID); // Generates an OpenGL texture object
	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes); // Assigns the image to the OpenGL Texture object
	glGenerateMipmap(texType); // Generates MipMaps

	stbi_image_free(bytes); // Deletes the image data as it is already in the OpenGL Texture object

	glBindTexture(texType, 0); // Unbinds the OpenGL Texture object so that it can't accidentally be modified
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform); // Gets the location of the uniform
	shader.Activate(); // Shader needs to be activated before changing the value of a uniform
	glUniform1i(texUni, unit); // Sets the value of the uniform
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}