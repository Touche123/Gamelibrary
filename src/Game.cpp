#include "Game.h"
#include <iostream>

Game::Game() {
	engine = new Engine();
}

void Game::Init() {
	engine->Init();
}
void Game::Run() {
	while (!engine->ShouldClose()) {
		engine->Update();
		engine->Render();
	}
}

void Game::SetCurrentScene(Scene* scene) {
	engine->SetCurrentScene(scene);
}

Game::~Game() {
	delete engine;
}
