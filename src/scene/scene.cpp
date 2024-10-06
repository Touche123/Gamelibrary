#include "scene.h"

#include "entity_system.h"
#include "../input_system.h"
#include "../physics_system.h"

Scene::Scene() {
	entity_system = new EntitySystem();
	physics_system = new PhysicsSystem();
}

Scene::~Scene() {
}

void Scene::initialize() {
	
}

void Scene::render(float deltaTime) {
}

void Scene::update(float deltaTime) {
	physics_system->update(deltaTime, *entity_system);
}

void Scene::handleInput(float deltaTime) {
}

void Scene::setCamera() {
}

void Scene::setSkybox() {
}

void Scene::setLighting() {
}

void Scene::AddEntity(Entity& e) {
	entity_system->AddEntity(e);
}
