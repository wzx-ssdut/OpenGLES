#include "Scene.hpp"


void CreateApplicationInstance() {
	new Sample("Blank Window", 400, 400);
}


bool Sample::initialize() {
	glViewport(0, 0, this->getWindowWidth(), this->getWindowHeight());
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	return true;
}


void Sample::finalize() {
}


void Sample::update(float dt) {
}


void Sample::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}
