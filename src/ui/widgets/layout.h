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

class HorizontalLayout : public Layout {
    void ApplyLayout(Container* container, std::vector<Widget*>& children) override;
};

class GridLayout : public Layout {
public:
    GridLayout(int columns);
    void ApplyLayout(Container* container, std::vector<Widget*>& children) override;
private:
    int columns;
};