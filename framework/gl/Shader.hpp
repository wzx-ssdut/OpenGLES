#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>

#include <GLES3/gl3.h>

class Shader {
public:
	Shader(const std::string& source, GLenum type);
	virtual ~Shader();

	operator bool() {
		return _name != 0;
	}

	GLuint getName() {
		return _name;
	}

protected:
	void printInfoLog();

protected:
	GLuint _name;
	GLenum _type;
};

class VertexShader final : public Shader {
public:
	VertexShader(const std::string& source) : Shader(source, GL_VERTEX_SHADER) {
	}
};

class FragmentShader final : public Shader {
public:
	FragmentShader(const std::string& source) : Shader(source, GL_FRAGMENT_SHADER) {
	}
};

#endif // SHADER_HPP