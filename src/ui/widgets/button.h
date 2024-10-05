#pragma once

#include <iostream>
#include <functional>
#include <string>

#include "widget.h"

class Button : public Widget {
public:
	using ClickCallback = std::function<void()>;

	Button(float x, float y, float width, float height, const std::string& label)
		: Widget(x, y, width, height), label(label), isDown(0), color({ 0.f, 0.f, 0.f }), clickCallback(nullptr) {}

	void SetClickCallback(ClickCallback callback) {
		clickCallback = callback;
	}

	void SetColor(const glm::vec3& color) {
		this->color = color;
	}

	void SetBorderColor(const glm::vec3& borderColor) {
		this->borderColor = borderColor;
	}

	void Render(UIRenderer* renderer) override {
		if (!IsVisible()) return;
		renderer->RenderButton(this);
	}

	std::string GetLabel() { return label; }
	glm::vec3 GetColor() { return color; }
	glm::vec3 GetBorderColor() { return borderColor; }
	bool GetIsHovered() { return isHovered; }
	bool GetIsDown() { return isDown; }

	// Handle mouse clicks
	void OnClick(float mouseX, float mouseY) override {
		if (clickCallback && IsInside(mouseX, mouseY)) {
			isDown = true;
			clickCallback(); // Trigger the button's callback if clicked
		} else {
			isDown = false;
		}
	}

	void OnMouseOver(float mouseX, float mouseY) override {
		isHovered = IsInside(mouseX, mouseY);
		//isDown = false;
	}

	void OnMouseDown(float mouseX, float mouseY) override {
		if (IsInside(mouseX, mouseY))
			isDown = true;
	}

	void OnMouseUp(float mouseX, float mouseY) override {
		isDown = false;
	}

private:
	std::string label;
	glm::vec3 color;
	glm::vec3 borderColor;
	bool isDown;
	ClickCallback clickCallback; // Callback for click event

	bool IsInside(float mouseX, float mouseY) {
		return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
	}
};