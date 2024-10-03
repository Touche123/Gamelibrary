#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "src/entity_system.h"
#include "src/mesh.h"
#include "src/input_system.h"
#include "src/physics_system.h"
#include "Input.h"
#include "src/ui/ui_manager.h"
#include "src/ui/widgets/uirenderer.h"
#include "Input.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Renderer renderer;

UIManager* ui;
UIRenderer* ui_renderer;
unsigned int SCR_WIDTH = 1600;
unsigned int SCR_HEIGHT = 900;

float deltaTime, currentFrame, lastFrame;

Mesh mesh;
EntitySystem entity_system;
InputSystem input_system;
PhysicsSystem physics_system;
Entity test_entity;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    renderer.Initialize(SCR_WIDTH, SCR_HEIGHT);
    Input::Initialize(window);
    
    ui = new UIManager(SCR_WIDTH, SCR_HEIGHT);
    ui_renderer = new UIRenderer();
    /*if (!ui->Initialize()) {
        return -1;
    }*/
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
    
    test_entity.addComponent("position", position_component);
    test_entity.addComponent("mesh", mesh_component);
    test_entity.addComponent("input", input_component);
    test_entity.addComponent("velocity", velocity_component);
    entity_system.AddEntity(test_entity);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        ui->Update(Input::GetMouseX(), Input::GetMouseY());

        auto currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        input_system.update(entity_system);
        physics_system.update(deltaTime, entity_system);
        renderer.render(entity_system);
        ui_renderer->UpdateProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);
        ui->Render(ui_renderer);
        glfwSwapBuffers(window);

        Input::EndFrame();
        
    }

    glfwTerminate();
}

void processInput(GLFWwindow* window)
{
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    /*if (Input::IsKeyDown(GLFW_KEY_TAB))
        ui->ToggleConsole(); 
    */

    if (ui->Exit_Application)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}
