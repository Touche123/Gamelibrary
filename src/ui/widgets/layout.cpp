#include "layout.h"
#include "container.h"

void VerticalLayout::ApplyLayout(Container* container, std::vector<Widget*>& children) {
    float currentY = container->GetPosition().y + container->GetSize().y;
    for (auto* child : children) {
        currentY -= child->GetSize().y + 50;
        child->SetPosition(container->GetPosition().x, currentY);
    }
}
