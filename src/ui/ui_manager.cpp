#include "ui_manager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../io/Input.h"
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
	panel1->SetLayout(new VerticalLayout());

	Button* button1 = new Button(0, 0, 200, 50, "Click me 1");
	button1->SetPadding(25);
	button1->SetMargin(5);
	
	button1->SetColor({ 60.f / 255.f, 99.f / 255.f, 130 / 255.f });
	button1->SetBorderColor(glm::vec3(98.f / 255.f, 163.f / 255.f, 188.f / 255.f));

	button1->SetClickCallback([this]() {
		Button1ClickHandler();
	});

	Button* button2 = new Button(0, 100, 200, 50, "Click me 2");
	button2->SetPadding(10);
	button2->SetMargin(15);
	button2->SetColor({ 1.f, 0.f, 0.f });
	button2->SetClickCallback([]() {
		std::cout << "Button 2 clicked" << std::endl;
	});

	Button* button3 = new Button(0, 200, 200, 50, "Click me 3");
	button3->SetPadding(10);
	button3->SetMargin(15);
	button3->SetColor({ 1.f, 0.f, 0.f });
	button3->SetClickCallback([]() {
	std::cout << "Button 3 clicked" << std::endl;
	});

	TextLabel* textlabel1 = new TextLabel(200, 400, "hejsan");
	textlabel1->SetPadding(10);
	textlabel1->SetMargin(10);

	panel1->AddChild(button1);
	panel1->AddChild(button2);
	panel1->AddChild(button3);
	panel1->AddChild(textlabel1);

	Container* panel2 = new Container(400, 100, 300, 300);
	GridLayout* layout = new GridLayout(2);
	panel2->SetLayout(layout);

	Button* button4 = new Button(0, 0, 200, 50, "Click me 4");
	button4->SetColor({ 1.f, 0.f, 0.f });
	button4->SetClickCallback([this]() {
		Button1ClickHandler();
		});

	Button* button5 = new Button(0, 100, 200, 50, "Click me 5");
	button5->SetColor({ 1.f, 0.f, 0.f });
	button5->SetClickCallback([]() {
		std::cout << "Button 5 clicked" << std::endl;
		});

	Button* button6 = new Button(0, 200, 200, 50, "Click me 6");
	button6->SetColor({ 1.f, 0.f, 0.f });
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

void UIManager::Update(float mouseX, float mouseY) {
	for (auto* widget : rootWidgets) {
		if (Input::IsMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
			widget->OnMouseUp(mouseX, mouseY);
		if (Input::IsMouseButtonDown(GLFW_MOUSE_BUTTON_1))
			widget->OnMouseDown(mouseX, mouseY);
		else
			widget->OnMouseOver(mouseX, mouseY);
	}
	
}
