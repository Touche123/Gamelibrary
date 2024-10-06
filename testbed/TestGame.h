#pragma once

#include <Game.h>
#include <scene/scene.h>

class TestGame : public Game {
public:
	TestGame() {
		Scene* scene = new Scene();
	}

	~TestGame() {
	}

	void Init() override {
		Game::Init();
	}

	void Run() override {
		Game::Run();
	}

	void SetCurrentScene(Scene* scene) override {
		Game::SetCurrentScene(scene);
	}
};