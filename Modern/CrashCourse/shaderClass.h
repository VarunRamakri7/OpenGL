#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get__file_contents(const char* filename);

class Shader
{
	public:
		GLuint ID;
		Shader(const char* fragmentFile, const char* vertexFile);

		void Activate();
		void Delete();
	private:
		void compileErrors(unsigned int shader, const char* type); // Checks if the different Shaders have compiled properly
};

#endif
