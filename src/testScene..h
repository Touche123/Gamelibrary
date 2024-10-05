#pragma once
#include "scene.h"

class TestScene : public Scene {
public:
	void initialize() override {
        Entity e;
        auto position_component = std::make_shared<PositionComponent>();
        position_component->position = glm::vec3(1.0f, 1.0f, 0.0f);
        auto mesh_component = std::make_shared<MeshComponent>();
        auto input_component = std::make_shared<InputComponent>();
        auto velocity_component = std::make_shared<VelocityComponent>();

        Vertex vertices[] = {
        {
            { 0.5f,  0.5f, 0.0f },  // position (top right)
            { 0.0f, 0.0f, 1.0f },    // normal
            { 1.0f, 1.0f }           // texture coordinates
        },
        {
            { 0.5f, -0.5f, 0.0f },  // position (bottom right)
            { 0.0f, 0.0f, 1.0f },    // normal
            { 1.0f, 0.0f }           // texture coordinates
        },
        {
            { -0.5f, -0.5f, 0.0f }, // position (bottom left)
            { 0.0f, 0.0f, 1.0f },    // normal
            { 0.0f, 0.0f }           // texture coordinates
        },
        {
            { -0.5f,  0.5f, 0.0f }, // position (top left)
            { 0.0f, 0.0f, 1.0f },    // normal
            { 0.0f, 1.0f }           // texture coordinates
        }
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        mesh_component->mesh = Mesh(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));

        e.addComponent("position", position_component);
		e.addComponent("mesh", mesh_component);
		e.addComponent("input", input_component);
		e.addComponent("velocity", velocity_component);
		entity_system.AddEntity(e);
	}

    void update(float deltaTime) override {
        input_system.update(entity_system);
        physics_system.update(deltaTime, entity_system);
    }
};