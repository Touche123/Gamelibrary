#pragma once
#include <glm/glm.hpp>

#include "uirenderer.h"

class Widget {
public:
	Widget(float x, float y, float width, float height)
		: x(x), y(y), width(width), height(height), visible(true) { }

	virtual ~Widget() {}

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }

	void SetVisible(bool visible) { this->visible = visible; }
	bool IsVisible() const{ return visible; }

	virtual void Render(UIRenderer* renderer) = 0;
	virtual void OnClick(float mouseX, float mouseY) {}

	glm::vec2 GetPosition() const {
		return glm::vec2(x, y);
	}

	glm::vec2 GetSize() const {
		return glm::vec2(width, height);
	}

protected:
	float x, y, width, height;
	bool visible;
};