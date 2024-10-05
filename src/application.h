#pragma once
#include "renderer.h"
#include "scene.h"
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