#include "ui_manager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Input.h"
#include <functional>
#include "widgets/textlabel.h"


UIManager::UIManager(int screenWidth, int screenHeight) :
	button(100, 200, 150, 50, "Play")
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	UpdateProjectionMatrix();
	button.SetOnClick([this]() {
		this->OnPlayButtonClicked();
		});

	fontManager.LoadFont("assets/fonts/arial.ttf", 24);
	_characters = fontManager.GetCharacters();

	TextLabel* label = new TextLabel(0.f, 50.f, "Hello", 24.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	TextLabel* consoleText = new TextLabel(_console.x, _console.y, "Hello", 24.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	AddTextLabel(label);
	AddTextLabel(consoleText);
}

void UIManager::AddTextLabel(TextLabel* label) {
	textLabels.push_back(label);
}

bool UIManager::ShouldExit() {
	return _shouldExit;
}

void UIManager::UpdateProjectionMatrix() {
	projectionMatrix = glm::ortho(0.0f, (float)_screenWidth, (float)_screenHeight, 0.0f); // Top-left origin

	//projectionMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void UIManager::OnPlayButtonClicked() {
	std::cout << "Play button clicked!????" << std::endl;
	_shouldExit = true;
}
bool UIManager::Initialize() {

	_shader = Shader("assets/shaders/OrthoShader.vs", "assets/shaders/OrthoShader.fs");
	text_shader = Shader("assets/shaders/textShader.vs", "assets/shaders/textShader.fs");

	_screenWidth = _screenWidth;
	_screenHeight = _screenHeight;
	//projectionMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	_quad2D[0] = glm::vec2(0, 1);
	_quad2D[1] = glm::vec2(0, 0);
	_quad2D[2] = glm::vec2(1, 1);
	_quad2D[3] = glm::vec2(1, 0);

	_console.enabled = false;
	_console.x = 0;
	_console.y = _screenHeight;
	_console.width = _screenWidth;
	_console.height = 50;
	UpdateConsole();

	

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_quad2D), _quad2D, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// configure VAO/VBO for texture quads
		// -----------------------------------
	glGenVertexArrays(1, &text_vao);
	glGenBuffers(1, &text_vbo);
	glBindVertexArray(text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

const glm::mat4& UIManager::GetProjectionMatrix() const {
	return projectionMatrix;
}

void UIManager::Draw() {
	
	_shader.use();
	_shader.setMat4("projection", projectionMatrix);
	glm::mat4 model = glm::mat4(1.0);
	_shader.setMat4("model", model);
	glBindVertexArray(_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	model = glm::translate(glm::mat4(1.0f), glm::vec3(_console.x, _console.y, 1));
	model = glm::scale(model, glm::vec3(_console.width, _console.height, 1));
	_shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	Render(_screenWidth, _screenHeight);

	button.HandleInput(Input::GetMouseX(), Input::GetMouseY(), Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1));
	button.Draw(_screenWidth, _screenHeight);
}

void UIManager::DrawMainMenu() {
	_shader.use();
	_shader.setMat4("projection", projectionMatrix);
	glm::mat4 model = glm::mat4(1.0);
	_shader.setMat4("model", model);
	glBindVertexArray(_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	model = glm::translate(glm::mat4(1.0f), glm::vec3(_screenWidth / 2 - 100, _screenHeight / 2 - 200, 1));
	model = glm::scale(model, glm::vec3(200, 400, 1));
	_shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void UIManager::ToggleConsole() {
	_console.enabled = !_console.enabled;
	UpdateConsole();
}

void UIManager::UpdateConsole() {
	if (_console.enabled) {
		_console.x = 0;
		_console.y = 0;
		_console.width = _screenWidth;
		_console.height = 50;
	} else {
		_console.width = _screenWidth;
		_console.height = 50;
		_console.x = 0;
		_console.y = -_console.height;
	}
}

float UIManager::CalculateTextHeight(std::string text, float scale) {
	float maxHeight = 0.0f;
	for (char c : text) {
		Character ch = _characters[c];
		float characterHeight = ch.Size.y * scale; // Calculate character height with scale

		if (characterHeight > maxHeight)
			maxHeight = characterHeight;
	}
	return maxHeight; // Return the maximum height found
}

void UIManager::Render(float screenWidth, float screenHeight) {
	for (const auto& label : textLabels) {
		RenderText(label->GetText(), label->GetPosition(), label->GetFontSize(), label->GetColor());
	}
}

void UIManager::RenderText(const std::string& text, const glm::vec2 position, float fontSize, glm::vec3 color) {
	float scale = 1;
	float textHeight = CalculateTextHeight(text, 1); // Calculate the height of the text
	float offsetY = textHeight; // Offset the y position by the height of the text

	text_shader.use();
	//text_shader.setMat4("projection", uiManager->GetProjectionMatrix());
	//text_shader.setMat4("projection", glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f)); // Top-left origin
	text_shader.setMat4("projection", glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight));

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// activate corresponding render state	
	text_shader.use();
	glUniform3f(glGetUniformLocation(text_shader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text_vao);

	// iterate through all characters
	std::string::const_iterator c;

	float x = position.x;
	float y = position.y;

	for (c = text.begin(); c != text.end(); c++) {
		Character ch = _characters[*c];

		float xpos = x + ch.Bearing.x * 1;
		float ypos = _screenHeight - y - (ch.Size.y - ch.Bearing.y) * scale - offsetY;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void UIManager::RenderButton(const Button* button) {

}