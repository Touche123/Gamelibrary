#pragma once

#include "widget.h"

class TextLabel : public Widget {
public:
	TextLabel(float x, float y, const std::string& text)
		: Widget(x, y, 0.0f, 0.0f), text(text) { }

	const std::string& GetText() const { return text; }

	void Render(UIRenderer* renderer) override {
		if (!IsVisible()) return;
		renderer->RenderText(this);
	}

private:
	std::string text;
};