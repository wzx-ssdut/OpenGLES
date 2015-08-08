#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>

#include <string>


class Application {
public:
	static Application* getInstance();
	static void createInstance();
	static void destroyInstance();

private:
	static Application* _instance;

public:
	Application(const std::string& title, int width, int height);
	virtual ~Application();

public:
	virtual bool initialize() = 0;
	virtual void finalize() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;

	bool createRenderContext(EGLNativeWindowType nativeWindow, EGLNativeDisplayType nativeDisplay);
	void destroyRenderContext();
	void swapBuffers();

public:
	int getWindowWidth() const {
		return _windowWidth;
	}
	int getWindowHeight() const {
		return _windowHeight;
	}
	const std::string& getWindowTitle() const {
		return _windowTitle;
	}
	float getAspectRatio() const {
		return (float)_windowWidth / (float)_windowHeight;
	}

protected:
	std::string _windowTitle;
	int _windowWidth;
	int _windowHeight;

private:
	EGLDisplay _display = nullptr;
	EGLSurface _surface = nullptr;
	EGLContext _context = nullptr;
};


extern void CreateApplicationInstance();


#endif // APPLICATION_HPP