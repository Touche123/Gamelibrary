#pragma once
#include "core/defines.h"
#include "core/Engine.h"

class GAMELIBRARY_API Game {
public:
	Game();
	~Game();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void SetCurrentScene(Scene* scene);

protected:
	Engine* engine;
};