#include "layout.h"
#include "container.h"

void VerticalLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentY = container->GetPosition().y + container->GetSize().y;

    for (auto* child : children) {
        currentY -= child->GetMargin();
        currentY -= child->GetSize().y;
        child->SetPosition(container->GetPosition().x + child->GetMargin(), currentY);
        currentY -= child->GetMargin();
    }
}

void HorizontalLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentX = container->GetPosition().x;

    for (auto* child : children) {
        currentX += child->GetMargin();
        child->SetPosition(currentX, container->GetPosition().y + child->GetMargin());
        currentX += child->GetSize().x;
        currentX += child->GetMargin();
    }
}

GridLayout::GridLayout(int columns) {
    this->columns = columns;
}

void GridLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentX = container->GetPosition().x;
    float currentY = container->GetPosition().y + container->GetSize().y; // Start from the top

    for (size_t i = 0; i < children.size(); ++i) {
        currentX += children[i]->GetMargin();
        currentY -= children[i]->GetMargin();

        // Set widget position with margins applied
        children[i]->SetPosition(currentX, currentY);

        if ((i + 1) % columns == 0) { // Move to the next row
            currentX = container->GetPosition().x; // Reset x position
            currentY -= children[i]->GetSize().y + children[i]->GetMargin(); // Move down for the next row
        } else {
            currentX += children[i]->GetSize().x + children[i]->GetMargin(); // Move right for the next child
        }
    }
}