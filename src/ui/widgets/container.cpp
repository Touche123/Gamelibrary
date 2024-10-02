#include "container.h"
#include "layout.h"

Container::Container(float x, float y, float width, float height)
	: Widget(x, y, width, height), layout(nullptr) {
}

void Container::AddChild(Widget* widget) {
	children.push_back(widget);
}

void Container::SetLayout(Layout* layout) {
	this->layout = layout;
}

void Container::Render(UIRenderer* renderer) {
	if (!IsVisible()) return;

	// Apply layout to position children
	if (layout) {
		layout->ApplyLayout(this, children);
	}

	// Render all children
	for (auto* child : children) {
		child->Render(renderer);
	}
}

void Container::OnClick(float mouseX, float mouseY) {
	// Forward the click event to the children
	for (auto* child : children) {
		child->OnClick(mouseX, mouseY);
	}
}
