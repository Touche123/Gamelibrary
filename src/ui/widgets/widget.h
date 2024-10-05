#pragma once
#include <glm/glm.hpp>

#include "../renderer/ui_renderer.h"

struct Color {
	float r, g, b, a;

	Color Blend(const Color& other, float factor) const {
		return {
			r * (1.0f - factor) + other.r * factor,
			g * (1.0f - factor) + other.g * factor,
			b * (1.0f - factor) + other.b * factor,
			a * (1.0f - factor) + other.a * factor
		};
	}

	Color Tint(float factor) const {
		// Tint the color towards white (increasing brightness)
		return Blend(Color{ 1.0f, 1.0f, 1.0f, a }, factor);
	}

	Color Darken(float factor) const {
		// Darken the color (decreasing brightness)
		return Blend(Color{ 0.0f, 0.0f, 0.0f, a }, factor);
	}
};

class Widget {
public:
	Widget(float x, float y, float width, float height)
		: x(x), y(y), width(width), height(height), padding(0), margin(0), isHovered(false), visible(true) { }

	virtual ~Widget() {}

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSize(float width, float height) { this->width = width; this->height = height; }

	void SetVisible(bool visible) { this->visible = visible; }
	bool IsVisible() const{ return visible; }

	virtual void Render(UIRenderer* renderer) = 0;
	virtual void OnClick(float mouseX, float mouseY) {}
	virtual void OnMouseDown(float mouseX, float mouseY) {}
	virtual void OnMouseUp(float mouseX, float mouseY) {}
	virtual void OnMouseOver(float mouseX, float mouseY) {}

	void SetPadding(float padding) { this->padding = padding; }
	void SetMargin(float margin) { this->margin = margin; }

	glm::vec2 GetPosition() const { return glm::vec2(x, y); }
	glm::vec2 GetSize() const { return glm::vec2(width, height); }

	float GetPadding() const { return padding; }
	float GetMargin() const { return margin; }

protected:
	float x, y, width, height;
	bool isHovered;
	float padding; // Space inside the widget border
	float margin; // Space outside the widget border
	bool visible; 
};

