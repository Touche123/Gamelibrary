#include "layout.h"
#include "container.h"

void VerticalLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentY = container->GetPosition().y + container->GetSize().y;
    for (auto* child : children) {
        currentY -= child->GetSize().y + 50;
        child->SetPosition(container->GetPosition().x, currentY);
    }
}

void HorizontalLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentX = container->GetPosition().x;
    for (auto* child : children) {
        child->SetPosition(currentX, container->GetPosition().y);
        currentX += child->GetSize().x;
    }
}

GridLayout::GridLayout(int columns) {
    this->columns = columns;
}

void GridLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentX = container->GetPosition().x;
    float currentY = container->GetPosition().y + container->GetSize().y; // Start from the top

    for (size_t i = 0; i < children.size(); ++i) {
        children[i]->SetPosition(currentX, currentY);
        if ((i + 1) % columns == 0) { // Move to the next row
            currentX = container->GetPosition().x; // Reset x position
            currentY -= children[i]->GetSize().y; // Move down for the next row
        } else {
            currentX += children[i]->GetSize().x; // Move right for the next child
        }
    }
}