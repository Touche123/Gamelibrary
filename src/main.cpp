#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "entity_system.h"
#include "mesh.h"
#include "input_system.h"
#include "physics_system.h"
#include "io/Input.h"
#include "ui/ui_manager.h"

#include "testScene..h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Renderer renderer;

UIManager* ui;
UIRenderer* ui_renderer;
unsigned int SCR_WIDTH = 1600;
unsigned int SCR_HEIGHT = 900;

float deltaTime, currentFrame, lastFrame;

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

    TestScene testScene;
    testScene.initialize();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        ui->Update(Input::GetMouseX(), Input::GetMouseY());

        auto currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        testScene.update(deltaTime);
        
        renderer.render(testScene.GetEntitySystem());

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
