#pragma once

#include "entity_system.h"
#include "input_system.h"
#include "physics_system.h"

class Scene {
public:

	Scene();
	~Scene();

	void initialize();

	void render(float deltaTime);

	void update(float deltaTime);

	void handleInput(float deltaTime);

	void setCamera();

	void setSkybox();
	
	void setLighting();

private:
	EntitySystem entity_system;
	InputSystem input_system;
	PhysicsSystem physics_system;
};
	
		