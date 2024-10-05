#pragma once

#include "entity_system.h"
#include "input_system.h"
#include "physics_system.h"

class Scene {
public:

	Scene();
	~Scene();

	virtual void initialize();

	void render(float deltaTime);

	virtual void update(float deltaTime);

	void handleInput(float deltaTime);

	void setCamera();

	void setSkybox();
	
	void setLighting();

	EntitySystem& GetEntitySystem() { return entity_system; }
	InputSystem& GetInputSystem() { return input_system; }
	PhysicsSystem& GetPhysicsSystem() { return physics_system; }

protected:
	EntitySystem entity_system;
	InputSystem input_system;
	PhysicsSystem physics_system;
};
	
		