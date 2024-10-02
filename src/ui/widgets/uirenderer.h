#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "font_renderer.h"

#include "../../../Shader.h"

class Button;

class UIRenderer {
public:
	UIRenderer();
	~UIRenderer();
	
	void Initialize();
	void DrawQuad(const glm::vec2& position, const glm::vec2& size);
	void UpdateProjectionMatrix(float screenWidth, float screenHeight);
	void RenderButton(Button* button);
	void RenderTextLabel(const std::string& text, const glm::vec2& position, float scale);

private:
	GLuint _quadVAO, _quadVBO;
	Shader _buttonShader, _textShader;
	glm::mat4 projectionMatrix;
	FontRenderer _fontRenderer;
	void InitializeQuad();
	
};