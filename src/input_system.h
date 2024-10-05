#pragma once
#include "scene/entity_system.h"
#include "io/Input.h"

class InputSystem {
public:
	InputSystem() {}

	void update(EntitySystem& entitySystem) {
		for (auto& entity : entitySystem.GetEntities()) {
			auto inputComponent = entity.getComponent<InputComponent>("input");
			auto velocityComponent = entity.getComponent<VelocityComponent>("velocity");

			if (inputComponent && velocityComponent) {
				
				handle_input(inputComponent);

				velocityComponent->velocity = inputComponent->movement_direction * 5.0f;
			}
		}
	}
	
private:

	void handle_input(std::shared_ptr<InputComponent>& inputComponent) {
		inputComponent->movement_direction = glm::vec3(0.f);

		if (Input::IsKeyPressed(GLFW_KEY_W)) {
			inputComponent->movement_direction.y = 1;
		}
		if (Input::IsKeyPressed(GLFW_KEY_S)) {
			inputComponent->movement_direction.y = -1;
		}
		if (Input::IsKeyPressed(GLFW_KEY_A)) {
			inputComponent->movement_direction.x = -1;
		}
		if (Input::IsKeyPressed(GLFW_KEY_D)) {
			inputComponent->movement_direction.x = 1;
		}
	}
};