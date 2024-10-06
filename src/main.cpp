//#include <iostream>
//#include "platform/platform_glfw.h"
//#include "rendering/Renderer.h"
//#include <string>
//#include <fstream>
//#include <sstream>
//#include "Shader.h"
//#include "scene/entity_system.h"
//#include "mesh.h"
//#include "input_system.h"
//#include "physics_system.h"
//#include "io/Input.h"
//#include "ui/ui_manager.h"
//
//#include "testScene..h"
//#include "application.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//Renderer renderer;
//Platform* platform = new GLFWPlatform();
//UIManager* ui;
//UIRenderer* ui_renderer;
//unsigned int SCR_WIDTH = 1600;
//unsigned int SCR_HEIGHT = 900;
//
//int main()
//{
//    platform->Init();
//    Application app(platform);
//    
//    renderer.Initialize(SCR_WIDTH, SCR_HEIGHT);
//    Input::Initialize(static_cast<GLFWPlatform*>(platform)->GetWindow());
//    
//    ui = new UIManager(SCR_WIDTH, SCR_HEIGHT);
//    ui_renderer = new UIRenderer();
//
//    TestScene testScene;
//    testScene.initialize();
//
//
//    //app.run();
//
//    while (!glfwWindowShouldClose(static_cast<GLFWPlatform*>(platform)->GetWindow()))
//    {
//        platform->PollEvents();
//        
//        processInput(static_cast<GLFWPlatform*>(platform)->GetWindow());
//        ui->Update(Input::GetMouseX(), Input::GetMouseY());
//        testScene.update(static_cast<GLFWPlatform*>(platform)->GetDeltaTime());
//        renderer.render(testScene.GetEntitySystem());
//        ui_renderer->UpdateProjectionMatrix(SCR_WIDTH, SCR_HEIGHT);
//        ui->Render(ui_renderer);
//        glfwSwapBuffers(static_cast<GLFWPlatform*>(platform)->GetWindow());
//
//        Input::EndFrame();
//    }
//    glfwTerminate();
//}
//
//void processInput(GLFWwindow* window)
//{
//    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
//        glfwSetWindowShouldClose(window, true);
//
//    /*if (Input::IsKeyDown(GLFW_KEY_TAB))
//        ui->ToggleConsole(); 
//    */
//
//    if (ui->Exit_Application)
//        glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//
//    SCR_WIDTH = width;
//    SCR_HEIGHT = height;
//}
