#pragma once
#include "Shader.h"
#include "src/mesh.h"
#include "src/entity_system.h"

class Renderer 
{
public:
	bool Initialize(unsigned int screenWidth, unsigned int screenHeight);
	bool render(EntitySystem& entitySystem);
	bool shutdown();

private:
	Shader _defaultShader;
	Mesh _mesh;
	unsigned int _VBO, _VAO, _EBO;
	glm::mat4 _projection = glm::mat4(1.0f);
};

