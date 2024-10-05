#include "Game.h"
#include <iostream>

Game::Game() {
	engine = new Engine();
	engine->Init();

	engine->Run();
}

Game::~Game() {
	delete engine;
}
