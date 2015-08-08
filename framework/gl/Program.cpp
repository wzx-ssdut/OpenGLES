#include "Program.hpp"


Program::Program(Shader& vertexShader, Shader& fragmentShader) {
	if (!vertexShader || !fragmentShader) {
		return;
	}

	_name = glCreateProgram();
	glAttachShader(_name, vertexShader.getName());
	glAttachShader(_name, fragmentShader.getName());
	glLinkProgram(_name);

	GLint status{ 0 };
	glGetProgramiv(_name, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		this->printInfoLog();
		_name = 0;
	}
}

Program::~Program() {
	glDeleteProgram(_name);
	GLint status;
	glGetProgramiv(_name, GL_DELETE_STATUS, &status);
	if (GL_FALSE == status) {
		this->printInfoLog();
		_name = 0;
	}
}


void Program::use() {
	glUseProgram(_name);
}

GLint Program::getUniformLocation(const char* uniformName) {
	return glGetUniformLocation(_name, uniformName);
}

void Program::printInfoLog() {
	GLint infoLogLength;
	glGetProgramiv(_name, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(_name, infoLogLength, nullptr, infoLog);
		std::cerr << "SHADER_ERROR: " << infoLog << '\n';
		delete[] infoLog;
	}
}