#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include "../../Shader.h"
#include "widgets/Button.h"
#include "font_manager.h"

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
	void Render(float screenWidth, float screenHeight);
	void AddTextLabel(TextLabel* label);
	const glm::mat4& GetProjectionMatrix() const;

	FontManager fontManager;

	glm::mat4 projectionMatrix;
private:
	int _screenWidth	= 0;
	int _screenHeight	= 0;
	bool _shouldExit = false;
	unsigned int _VBO	= 0;
	unsigned int _VAO	= 0;
	Button button;
	
	glm::vec2 _quad2D[4];
	Shader _shader;
	Console _console;
	
	void OnPlayButtonClicked();
	void UpdateConsole();
	void DrawMainMenu();
	void UpdateProjectionMatrix();

	std::vector<TextLabel*> textLabels;
	std::vector<Button*> buttons;
	std::map<GLchar, Character> _characters;

	float CalculateTextHeight(std::string text, float scale);
	void RenderText(const std::string& text, const glm::vec2 position, float fontSize, glm::vec3 color);
	void RenderButton(const Button* button);

	unsigned int text_vao = 0;
	unsigned int text_vbo = 0;

	Shader text_shader;
};

