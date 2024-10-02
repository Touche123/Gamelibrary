#pragma once

#include <iostream>
#include <functional>
#include <string>

#include "widget.h"

class Button : public Widget {
public:
	using ClickCallback = std::function<void()>;

	Button(float x, float y, float width, float height, const std::string& label)
		: Widget(x, y, width, height), label(label), clickCallback(nullptr) { }

	void SetClickCallback(ClickCallback callback) {
		clickCallback = callback;
	}

	void Render(UIRenderer* renderer) override {
		if (!IsVisible()) return;
		renderer->RenderButton(this);
	}

	std::string GetLabel() { return label; }
	// Handle mouse clicks
	void OnClick(float mouseX, float mouseY) override {
		if (clickCallback && IsInside(mouseX, mouseY)) {
			clickCallback(); // Trigger the button's callback if clicked
		}
	}

	//// Handle input and trigger the OnClick event if needed
	//void HandleInput(float mouseX, float mouseY, bool mousePressed) override {
	//	// Check if the mouse is inside the button
	//	if (mouseX >= position.x && mouseX <= position.x + size.x &&
	//		mouseY >= position.y && mouseY <= position.y + size.y) {
	//		if (mousePressed) {
	//			if (clickCallback) {
	//				clickCallback();  // Invoke the assigned callback
	//			}
	//		}
	//	}
	//}

private:
	std::string label;
	ClickCallback clickCallback; // Callback for click event

	bool IsInside(float mouseX, float mouseY) {
		return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
	}
};