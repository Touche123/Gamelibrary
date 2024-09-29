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

#include "Ui.h"
#include "Input.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Renderer renderer;
Ui* ui;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Mesh mesh;
EntitySystem entity_system;
Entity test_entity;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
    
    ui = new Ui(SCR_WIDTH, SCR_HEIGHT);
    if (!ui->Initialize()) {
        return -1;
    }
    auto position_component = std::make_shared<PositionComponent>();
    position_component->position = glm::vec3(1.0f, 1.0f, 0.0f);
    auto mesh_component = std::make_shared<MeshComponent>();

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


    entity_system.AddEntity(test_entity);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        processInput(window);
        renderer.render(entity_system);
        ui->Draw();
        glfwSwapBuffers(window);
        
    }

    glfwTerminate();
}

void processInput(GLFWwindow* window)
{
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (Input::IsKeyDown(GLFW_KEY_TAB))
        ui->ToggleConsole();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
