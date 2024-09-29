#include "ui_manager.h"
#include <iostream>
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

	label = new TextLabel(this);
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


	//RenderText(_textShader, "This is a sample text", 125.0f, 125.0f, 1.0f, glm::vec3(1.f, 0.0f, 0.0f));
	//RenderText(_textShader, "This is a sample text", _console.x, _console.y + 5, 1.0f, glm::vec3(1.f, 0.0f, 0.0f));

	label->Render(_screenWidth, _screenHeight, "This is a sample text using label widget", _console.x, _console.y + 5, 1.0f, glm::vec3(1.f, 0.0f, 0.0f));

	label->Render(_screenWidth, _screenHeight, "This is a sample text using label widget", 300.f, 300, 1.0f, glm::vec3(1.f, 0.0f, 0.0f));

	//DrawMainMenu();

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