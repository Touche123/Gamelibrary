// testbed.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <core/Engine.h>
#include <scene/entity.h>
#include <Game.h>

#include "TestGame.h"

int main()
{
    Game* game = new TestGame();
    
    game->Init();

    Scene* scene = new Scene();
    Entity* e = new Entity();

    auto position_component = std::make_shared<PositionComponent>();
    auto velocity_component = std::make_shared<VelocityComponent>();
    velocity_component->velocity.x = 1;
    e->addComponent("position", position_component);
    e->addComponent("velocity", velocity_component);

    scene->AddEntity(*e);
    
    game->SetCurrentScene(scene);

    game->Run();

    delete game;
}

//Entity e;
//auto position_component = std::make_shared<PositionComponent>();
//position_component->position = glm::vec3(1.0f, 1.0f, 0.0f);
//auto mesh_component = std::make_shared<MeshComponent>();
//auto input_component = std::make_shared<InputComponent>();
//auto velocity_component = std::make_shared<VelocityComponent>();
//
//Vertex vertices[] = {
//{
//    { 0.5f,  0.5f, 0.0f },  // position (top right)
//    { 0.0f, 0.0f, 1.0f },    // normal
//    { 1.0f, 1.0f }           // texture coordinates
//},
//{
//    { 0.5f, -0.5f, 0.0f },  // position (bottom right)
//    { 0.0f, 0.0f, 1.0f },    // normal
//    { 1.0f, 0.0f }           // texture coordinates
//},
//{
//    { -0.5f, -0.5f, 0.0f }, // position (bottom left)
//    { 0.0f, 0.0f, 1.0f },    // normal
//    { 0.0f, 0.0f }           // texture coordinates
//},
//{
//    { -0.5f,  0.5f, 0.0f }, // position (top left)
//    { 0.0f, 0.0f, 1.0f },    // normal
//    { 0.0f, 1.0f }           // texture coordinates
//}
//};
//
//unsigned int indices[] = {  // note that we start from 0!
//    0, 1, 3,  // first Triangle
//    1, 2, 3   // second Triangle
//};
//
//mesh_component->mesh = Mesh(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
//
//e.addComponent("position", position_component);
//e.addComponent("mesh", mesh_component);
//e.addComponent("input", input_component);
//e.addComponent("velocity", velocity_component);
//entity_system->AddEntity(e);