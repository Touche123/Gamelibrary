#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "../../Shader.h"
#include "Button.h"
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
	bool ShouldExit();

private:
	int _screenWidth	= 0;
	int _screenHeight	= 0;
	bool _shouldExit = false;
	unsigned int _VBO	= 0;
	unsigned int _VAO	= 0;
	unsigned int _textVAO = 0;
	unsigned int _textVBO = 0;
	std::map<GLchar, Character> _characters;
	Button button;
	glm::mat4 _orthoMatrix;
	glm::vec2 _quad2D[4];
	Shader _shader;
	Shader _textShader;
	Console _console;
	FT_Library _freeFontLib;
	
	void OnPlayButtonClicked();
	void UpdateConsole();
	void DrawMainMenu();
	void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
	bool InitializeText();

};

