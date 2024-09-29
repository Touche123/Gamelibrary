#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
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
	bool Initialize();
	void Draw();
	void ToggleConsole();
	bool ShouldExit();
	const glm::mat4& GetProjectionMatrix() const;
	
	glm::mat4 projectionMatrix;
private:
	int _screenWidth	= 0;
	int _screenHeight	= 0;
	bool _shouldExit = false;
	unsigned int _VBO	= 0;
	unsigned int _VAO	= 0;
	Button button;
	TextLabel* label;
	
	glm::vec2 _quad2D[4];
	Shader _shader;
	Console _console;
	
	void OnPlayButtonClicked();
	void UpdateConsole();
	void DrawMainMenu();
	void UpdateProjectionMatrix();
};

