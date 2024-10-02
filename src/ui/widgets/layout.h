#pragma once

#include <vector>

class Container;
class Widget;

class Layout {
public:
    virtual void ApplyLayout(Container* container, std::vector<Widget*>& children) = 0;
};

class VerticalLayout : public Layout {
public:
    void ApplyLayout(Container* container, std::vector<Widget*>& children) override;
};