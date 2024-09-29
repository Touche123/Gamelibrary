#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


bool Renderer::Initialize(unsigned int screenWidth, unsigned int screenHeight)
{
    _projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return false;

    _defaultShader = Shader("assets/shaders/defaultShader.vs", "assets/shaders/defaultShader.fs");

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

    _mesh = Mesh(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(unsigned int));
    
    
    //glGenVertexArrays(1, &_VAO);
    //glGenBuffers(1, &_VBO);
    //glGenBuffers(1, &_EBO);
    //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //glBindVertexArray(_VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    //// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    //// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    ////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    //// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);
}

bool Renderer::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    glm::mat4 view = glm::mat4(1.0f);
    
    glm::mat4 model = glm::mat4(1.0f);

    
    view = glm::translate(view, glm::vec3(0.f, 0.0f, -3.0f));
    _defaultShader.use();
    _defaultShader.setMat4("projection", _projection);
    _defaultShader.setMat4("view", view);
    _defaultShader.setMat4("model", model);

    _mesh.Draw(_defaultShader);
    //glBindVertexArray(_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return false;
}

bool Renderer::shutdown()
{
	return false;
}
