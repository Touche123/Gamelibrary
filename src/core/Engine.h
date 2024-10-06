#pragma once
#include "defines.h"
#include "../scene/scene.h"
#include "../platform/platform.h"

class GAMELIBRARY_API Engine {
public:
	Engine();
	~Engine();
	void Init();
	void SetCurrentScene(Scene* scene);
	void Update();
	void Render();
	void ShutDown();
	bool ShouldClose();
	
private:
	Platform* platform;
	Scene* currentScene;
};