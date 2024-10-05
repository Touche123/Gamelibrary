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
}

bool Renderer::render(EntitySystem& entitySystem)
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

    for (const auto& entity : entitySystem.GetEntities()) {
        auto positionComponent = entity.getComponent<PositionComponent>("position");
        auto meshComponent = entity.getComponent<MeshComponent>("mesh");

        if (positionComponent && meshComponent) {
            model = glm::translate(model, positionComponent->position);
            _defaultShader.setMat4("model", model);
            meshComponent->mesh.Draw(_defaultShader);
        }
    }

	return false;
}

bool Renderer::shutdown()
{
	return false;
}
