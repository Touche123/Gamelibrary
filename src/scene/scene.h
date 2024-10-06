#pragma once
#include "../core/defines.h"

class EntitySystem;
class InputSystem;
class PhysicsSystem;
class Entity;

class GAMELIBRARY_API Scene {
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

	void AddEntity(Entity& e);

	EntitySystem& GetEntitySystem() { return *entity_system; }
	InputSystem& GetInputSystem() { return *input_system; }
	PhysicsSystem& GetPhysicsSystem() { return *physics_system; }

protected:
	EntitySystem* entity_system;
	InputSystem* input_system;
	PhysicsSystem* physics_system;
};
	
		