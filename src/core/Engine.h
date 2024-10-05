#pragma once
#include "defines.h"
#include "../platform/platform.h"

class GAMELIBRARY_API Engine {
public:
	Engine();
	~Engine();
	void Init();
	void SetCurrentScene();
	void Run();
	
private:
	Platform* platform;
};