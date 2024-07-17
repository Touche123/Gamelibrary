#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


struct Console {
	bool enabled;
	int x;
	int y;
	int width;
	int height;
};

class Ui {
public:
	Ui();
	Ui(int screenWidth, int screenHeight);
	void Draw();
	void ToggleConsole();
private:
	glm::mat4 _orthoMatrix;
	int _screenWidth;
	int _screenHeight;
	Shader _shader;
	unsigned int _VBO, _VAO;
	glm::vec2 _quad2D[4];
	Console _console;

	void UpdateConsole();
};

