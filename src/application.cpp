#include "application.h"

Application::Application(Platform* platform) : platform(platform), currentScene(nullptr) {
	renderer = new Renderer();
}

Application::~Application() {
	delete renderer;
	delete platform;
}

void Application::initialize() {
}

void Application::run() {
	if (!platform->Init()) {
		std::cerr << "Failed to initialize platform!" << std::endl;
		return;
	}
	
	int width, height;
	platform->GetWindowSize(width, height);
	renderer->Initialize(width, height);

	while (!platform->ShouldClose()) {
		platform->PollEvents();

		platform->SwapBuffers();
	}
}

void Application::update() {
}

void Application::lateUpdate() {
}
