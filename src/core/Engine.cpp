#include "Engine.h"

#include <iostream>

#include "../platform/platform_glfw.h"
#include "../scene/entity_system.h"

Engine::Engine() {
}

Engine::~Engine() {
	delete platform;
	std::cout << "Engine shutting down.." << std::endl;
}

void Engine::Init() {
	std::cout << "Engine initializing.." << std::endl;

	platform = new GLFWPlatform();

	if (platform->Init()) {
		std::cout << "Platform initialized.." << std::endl;
	} else {
		std::cout << "Error: Failed to initialize platform.." << std::endl;
	}

	std::cout << "Engine initialized.." << std::endl;
}

void Engine::Update() {
	platform->PollEvents();

	if (currentScene != nullptr) {
		currentScene->update(platform->GetDeltaTime());
	}
}

void Engine::SetCurrentScene(Scene* scene) {
	currentScene = scene;
}

void Engine::Render() {
	platform->SwapBuffers();
}

bool Engine::ShouldClose() {
	return platform->ShouldClose();
}

void Engine::ShutDown() {
	delete platform;
}