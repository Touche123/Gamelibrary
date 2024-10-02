#include "ui_manager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Input.h"
#include <functional>
#include "widgets/textlabel.h"
#include "widgets/container.h"
#include "widgets/layout.h"

void UIManager::Button1ClickHandler() {
	Exit_Application = true;
}

UIManager::UIManager(int screenWidth, int screenHeight)
{
	Container* panel = new Container(100, 100, 300, 300);
	VerticalLayout* layout = new VerticalLayout();
	panel->SetLayout(layout);

	Button* button1 = new Button(0, 0, 200, 50, "Click me 1");
	button1->SetClickCallback([this]() {
		Button1ClickHandler();
	});

	Button* button2 = new Button(0, 0, 200, 50, "Click me 2");
	button2->SetClickCallback([]() {
		std::cout << "Button 2 clicked" << std::endl;
	});

	Button* button3 = new Button(0, 0, 200, 50, "Click me 3");
	button3->SetClickCallback([]() {
	std::cout << "Button 3 clicked" << std::endl;
	});

	TextLabel* textlabel = new TextLabel(200, 400, "hejsan");

	panel->AddChild(button1);
	panel->AddChild(button2);
	panel->AddChild(button3);
	panel->AddChild(textlabel);

	AddWidget(panel);
}

void UIManager::AddWidget(Widget* widget) {
	rootWidgets.push_back(widget);
}

void UIManager::Render(UIRenderer* renderer) {
	for (auto* widget : rootWidgets) {
		widget->Render(renderer);
	}
}

void UIManager::ProcessClick(float mouseX, float mouseY) {
	for (auto* widget : rootWidgets) {
		widget->OnClick(mouseX, mouseY);
	}
}
