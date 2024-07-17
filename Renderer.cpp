#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Renderer::Initialize()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return false;
}

bool Renderer::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return false;
}

bool Renderer::shutdown()
{
	return false;
}
