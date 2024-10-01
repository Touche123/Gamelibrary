#pragma once

#include <iostream>
#include <functional>
#include <string>

#include "widget.h"

class Button : public Widget {
public:
	using ClickCallback = std::function<void()>;

	Button() {}
	Button(float x, float y, float width, float height, const std::string& label)
		: Widget(x, y, width, height), label(label) 
	{
	}

	// Handle input and trigger the OnClick event if needed
	void HandleInput(float mouseX, float mouseY, bool mousePressed) override {
		// Check if the mouse is inside the button
		if (mouseX >= position.x && mouseX <= position.x + size.x &&
			mouseY >= position.y && mouseY <= position.y + size.y) {
			if (mousePressed) {
				if (clickCallback) {
					clickCallback();  // Invoke the assigned callback
				}
			}
		}
	}

	void SetClickCallback(ClickCallback callback) {
		clickCallback = callback;
	}

	const std::string& GetLabel() const { return label; }
	glm::vec2 GetPosition() const { return glm::vec2(position.x, position.y); } // Assuming you have x and y members in Widget
	glm::vec2 GetSize() const { return glm::vec2(size.x, size.y); } // Assuming you have width and height in Widget

private:
	std::string label;
	ClickCallback clickCallback; // Callback for click event
};