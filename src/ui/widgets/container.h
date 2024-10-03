#pragma once

#include <vector>

#include "widget.h"

class Layout;

class Container : public Widget {
public:
    Container(float x, float y, float width, float height);

    void AddChild(Widget* widget);

    void SetLayout(Layout* layout);

    void Render(UIRenderer* renderer) override;

    void OnClick(float mouseX, float mouseY) override;

    void OnMouseDown(float mouseX, float mouseY) override;

    void OnMouseUp(float mosueX, float mouseY) override;

    void OnMouseOver(float mouseX, float mouseY) override;

private:
    std::vector<Widget*> children;
    Layout* layout; // The layout manager (e.g., grid, vertical stack)
};