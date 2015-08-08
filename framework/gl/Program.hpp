#ifndef __PROGRAM_HPP__
#define __PROGRAM_HPP__

#include <GLES3/gl3.h>

#include "Shader.hpp"


class Program {
public:
	Program(Shader& vertexShader, Shader& fragmentShader);
	Program(const Program&) = delete;
	~Program();

	GLuint getName();
	void use();

	GLint getUniformLocation(const char* uniformName);

private:
	void printInfoLog();

private:
	GLuint _name{ 0 };
};


#endif // __PROGRAM_HPP__