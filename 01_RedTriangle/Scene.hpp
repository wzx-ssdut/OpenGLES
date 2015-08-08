#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <Application.hpp>

class Program;

class Sample final : public Application {
public:
	using Application::Application;

public:
	virtual bool initialize() override;
	virtual void finalize() override;
	virtual void update(float dt) override;
	virtual void render() override;

private:
	Program* _program{ nullptr };
};


#endif // SAMPLE_HPP