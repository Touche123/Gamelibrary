#pragma once
#include "../Shader.h"
#include "../scene/entity_system.h"

class Renderer 
{
public:
	bool Initialize(unsigned int screenWidth, unsigned int screenHeight);
	bool render(EntitySystem& entitySystem);
	bool shutdown();

private:
	Shader _defaultShader;
	glm::mat4 _projection = glm::mat4(1.0f);
};

