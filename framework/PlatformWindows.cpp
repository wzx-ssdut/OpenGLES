#include "PlatformWindows.hpp"


#include <iostream>
#include <chrono>
#include <thread>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return result;
}


PlatformWindows::PlatformWindows() {
	_hWnd = nullptr;
	_hDC = nullptr;
}
PlatformWindows::~PlatformWindows() {
	this->destroyNativeWindow();
}


bool PlatformWindows::createNativeWindow() {
	const char* className = "OpenGLES3";
	DWORD style = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;
	HINSTANCE hInstance = GetModuleHandle(nullptr);


	WNDCLASS wc = { 0 };
	wc.style = CS_OWNDC;
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = className;
	if (!RegisterClass(&wc)) {
		std::cerr << "RegisterClass failed.\n";
		return false;
	}

	int width = Application::getInstance()->getWindowWidth();
	int height = Application::getInstance()->getWindowHeight();
	const char* title = Application::getInstance()->getWindowTitle().c_str();

	RECT rect;
	SetRect(&rect, 0, 0, width, height);
	AdjustWindowRect(&rect, style, FALSE);
	_hWnd = CreateWindow(className, title, style,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, hInstance, nullptr);
	if (_hWnd == nullptr) {
		std::cerr << "CreateWindow failed.\n";
		return false;
	}

	_hDC = GetDC(_hWnd);

	return true;
}
void PlatformWindows::destroyNativeWindow() {
	if (_hDC != nullptr && _hWnd != nullptr) {
		ReleaseDC(_hWnd, _hDC);
		DestroyWindow(_hWnd);
		_hWnd = nullptr;
		_hDC  = nullptr;
	}
}


void PlatformWindows::run() {
	Application* app = Application::getInstance();
	if (app == nullptr) {
		std::cerr << "Application::getInstance failed.\n";
		return;
	}

	if (!this->createNativeWindow()) {
		std::cerr << "CreateNativeWindow failed.\n";
		return;
	}

	if (!app->createRenderContext(this->getNativeWindow(), this->getNativeDisplay())) {
		std::cerr << "CreateRenderContext failed.\n";
		return;
	}

	if (!app->initialize()) {
		std::cerr << "Application initialize failed.\n";
		return;
	}

	ShowWindow(_hWnd, TRUE);

	this->loop();
}


void PlatformWindows::loop() {
	const std::chrono::duration<float> kAnimationInterval(1.0f / 60.0f); // 60 FPS
	std::chrono::duration<float> interval;

	std::chrono::time_point<std::chrono::high_resolution_clock> last, now;
	last = std::chrono::high_resolution_clock::now();

	Application* app = Application::getInstance();

	while (this->handleEvents()) {
		now = std::chrono::high_resolution_clock::now();
		interval = now - last;
		if (interval > kAnimationInterval) {
			last = now;
			app->update(interval.count());
			app->render();
			app->swapBuffers();
		}
		else {
			std::this_thread::sleep_for(std::chrono::microseconds(0));
		}
	}
}


bool PlatformWindows::handleEvents() {
	MSG msg;
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}


// Main Entry
int main() {
	Application::createInstance();

	PlatformWindows platform;
	platform.run();

	Application::destroyInstance();
}
