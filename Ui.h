#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Console {
	bool enabled;
	int x;
	int y;
	int width;
	int height;
};

struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

class Ui {
public:
	Ui(int screenWidth, int screenHeight);
	bool Initialize();
	void Draw();
	void ToggleConsole();
private:
	glm::mat4 _orthoMatrix;
	int _screenWidth = 0;
	int _screenHeight = 0;
	Shader _shader;
	unsigned int _VBO, _VAO = 0;
	glm::vec2 _quad2D[4];
	Console _console;
	FT_Library _freeFontLib;
	void UpdateConsole();
	bool InitializeText();
};

