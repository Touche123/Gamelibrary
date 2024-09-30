#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include "../ui_manager.h"

#include "../../../Shader.h"

class TextLabel {
public:
	TextLabel(float x, float y, const std::string text, float fontSize, glm::vec3 color) 
	: position(x, y), text(text), fontSize(fontSize), color(color) { }

	glm::vec2 GetPosition() const { return position; }
	const std::string& GetText() const { return text; }
	float GetFontSize() const { return fontSize; }
	glm::vec3 GetColor() const { return color; }

	void SetText(const std::string& newText) { text = newText; }
	void SetColor(glm::vec3 newColor) { color = newColor; }
private:
	glm::vec2 position;
	std::string text;
	float fontSize;
	glm::vec3 color;
};