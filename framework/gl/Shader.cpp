#include "Shader.hpp"

#include <iostream>


Shader::Shader(const std::string& source, GLenum type) {
	const char* s = source.c_str();

	_type = type;
	_name = glCreateShader(_type);
	glShaderSource(_name, 1, &s, nullptr);
	glCompileShader(_name);

	GLint status = 0;
	glGetShaderiv(_name, GL_COMPILE_STATUS, &status);
	if (GL_FALSE == status) {
		this->printInfoLog();
		_name = 0;
	}
}

Shader::~Shader() {
	int status;
	glDeleteShader(_name);
	glGetShaderiv(_name, GL_DELETE_STATUS, &status);
	if (GL_FALSE == status) {
		std::cerr << "DeleteShader failed.\n";
	}
}


void Shader::printInfoLog() {
	int infoLogLength;
	glGetShaderiv(_name, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		char* infoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(_name, infoLogLength, nullptr, infoLog);
		std::cerr << "SHADER_ERROR: " << infoLog << '\n';
		delete[] infoLog;
	}
}