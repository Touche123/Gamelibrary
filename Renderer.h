#pragma once
#include "Shader.h"

class Renderer 
{
public:
	bool Initialize(unsigned int screenWidth, unsigned int screenHeight);
	bool render();
	bool shutdown();

private:
	Shader _defaultShader;
	unsigned int _VBO, _VAO, _EBO;
	glm::mat4 _projection = glm::mat4(1.0f);
};

