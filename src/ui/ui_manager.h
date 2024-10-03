#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include "../../Shader.h"
#include "widgets/Button.h"

class TextLabel;

struct Console {
	bool enabled;
	int x;
	int y;
	int width;
	int height;
};

class UIManager {
public:
	UIManager(int screenWidth, int screenHeight);

	void AddWidget(Widget* widget);
	void Render(UIRenderer* renderer);
	void Update(float mouseX, float mouseY);

	void Button1ClickHandler();

	bool Exit_Application;
private:
	std::vector<Widget*> rootWidgets; // The main UI elements (e.g., main panels)
};

