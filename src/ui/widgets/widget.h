#pragma once
#include <glm/glm.hpp>

class Widget {
public:
	float x, y;
	float width, height;

	Widget () {}
	Widget(float x, float y, float width, float height)
		: position(x, y), size(width, height), is_visible(true) { }

	virtual ~Widget() = default;

	virtual void Draw(int screenWidth, int screenHeight) {
		if (!is_visible) return;
	}

	virtual void HandleInput(float mouseX, float mouseY, bool mousePressed) {
		// Check if mouse is inside the widget
		if (mouseX >= position.x && mouseX <= position.x + size.x &&
			mouseY >= position.y && mouseY <= position.y + size.y) {
			if (mousePressed) {
				OnClick();
			}
		}
	}
protected:
	glm::vec2 position;
	glm::vec2 size;
	bool is_visible;

	virtual void OnClick() {
		// Implement click behavior in derived classes
	}
};