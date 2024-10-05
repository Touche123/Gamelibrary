#pragma once

#include <string>

#include "widget.h"

class CheckBox : public Widget {
public:
	CheckBox(float x, float y, float width, float height, const std::string& label)
		: Widget(x, y, width, height), label(label) { }

	void Render(UIRenderer* renderer) override {
		if (!IsVisible()) return;
			renderer->RenderCheckBox(this);
	}

	glm::vec3 GetBackgroundColor() { return backgroundColor; }
	glm::vec3 GetBorderColor() { return borderColor; }
	std::string GetLabel() { return label; }
private:
	std::string label;
	glm::vec3 backgroundColor;
	glm::vec3 borderColor;
};