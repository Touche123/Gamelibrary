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
	Container* panel1 = new Container(100, 100, 300, 300);

	Button* button1 = new Button(0, 0, 200, 50, "Click me 1");
	button1->SetClickCallback([this]() {
		Button1ClickHandler();
	});

	Button* button2 = new Button(0, 100, 200, 50, "Click me 2");
	button2->SetClickCallback([]() {
		std::cout << "Button 2 clicked" << std::endl;
	});

	Button* button3 = new Button(0, 200, 200, 50, "Click me 3");
	button3->SetClickCallback([]() {
	std::cout << "Button 3 clicked" << std::endl;
	});

	TextLabel* textlabel1 = new TextLabel(200, 400, "hejsan");

	panel1->AddChild(button1);
	panel1->AddChild(button2);
	panel1->AddChild(button3);
	panel1->AddChild(textlabel1);

	Container* panel2 = new Container(400, 100, 300, 300);
	GridLayout* layout = new GridLayout(2);
	panel2->SetLayout(layout);

	Button* button4 = new Button(0, 0, 200, 50, "Click me 4");
	button4->SetClickCallback([this]() {
		Button1ClickHandler();
		});

	Button* button5 = new Button(0, 100, 200, 50, "Click me 5");
	button5->SetClickCallback([]() {
		std::cout << "Button 5 clicked" << std::endl;
		});

	Button* button6 = new Button(0, 200, 200, 50, "Click me 6");
	button6->SetClickCallback([]() {
		std::cout << "Button 6 clicked" << std::endl;
		});

	TextLabel* textlabel2 = new TextLabel(200, 400, "hejsan");

	panel2->AddChild(button4);
	panel2->AddChild(button5);
	panel2->AddChild(button6);
	panel2->AddChild(textlabel2);

	AddWidget(panel1);
	AddWidget(panel2);
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
