#pragma once
#include "rendering/renderer.h"
#include "scene/scene.h"
#include "platform/platform.h"

class Application {
public:
	Application(Platform* platform);
	~Application();
	void initialize();
	void update();
	void lateUpdate();
	void render();

	void run();

private:
	Platform* platform;
	Renderer* renderer;
	Scene* currentScene;
};