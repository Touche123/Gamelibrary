#pragma once
#include "entity_system.h"

class PhysicsSystem {
public:
	void update(float deltaTime, EntitySystem& entitySystem) {
		for (auto& entity : entitySystem.GetEntities()) {
			auto positionComponent = entity.getComponent<PositionComponent>("position");
			auto velocityComponent = entity.getComponent<VelocityComponent>("velocity");

			if (positionComponent && velocityComponent) {
				positionComponent->position += velocityComponent->velocity * deltaTime;
			}
		}
	}
};