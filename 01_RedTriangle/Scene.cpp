#include "Scene.hpp"

#include "gl/Program.hpp"

void CreateApplicationInstance() {
	new Sample("Red Triangle", 400, 400);
}

const GLuint kPositionIndex = 0;
const GLuint kColorIndex = 1;

bool Sample::initialize() {
	const char vertexShaderSource[]{ R"(
		#version 300 es
		layout(location = 0) in vec4 a_position;
		layout(location = 1) in vec4 a_color;
		smooth out vec4 v_color;
		void main() {
			gl_Position = a_position;
			v_color = a_color;
		}
	)"};
	const char fragmentShaderSource[]{ R"(
		#version 300 es
		precision mediump float;
		smooth in vec4 v_color;
		layout(location = 0) out vec4 color;
		void main() {
			color = v_color;
		}
	)" };

	VertexShader vertexShader{ vertexShaderSource };
	FragmentShader fragmentShader{ fragmentShaderSource };
	_program = new Program{ vertexShader, fragmentShader };

	// Setup viewport
	glViewport(0, 0, this->getWindowWidth(), this->getWindowHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	return true;
}

void Sample::render() {
	// Clear the color buffer.
	glClear(GL_COLOR_BUFFER_BIT);

	_program->use();

	const GLfloat positions[] = {
		-0.5f, -0.5f, 0.0f,
		+0.5f, -0.5f, 0.0f,
		+0.0f, +0.5f, 0.0f
	};
	const GLfloat color[] = {
		1.0f, 0.0f, 0.0f, 1.0f
	};

	glEnableVertexAttribArray(kPositionIndex);
	glVertexAttribPointer(kPositionIndex, 3, GL_FLOAT, GL_FALSE, 0, positions);

	glDisableVertexAttribArray(kColorIndex);
	glVertexAttrib4fv(kColorIndex, color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();
}

void Sample::finalize() {
	if (_program) {
		delete _program;
		_program = nullptr;
	}
}

void Sample::update(float dt) {

}
