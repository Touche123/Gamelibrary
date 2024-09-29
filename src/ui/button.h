#pragma once

#include <iostream>
#include <functional>
#include <string>

#include "widget.h"

class Button : public Widget {
public:
	Button() {}
	Button(float x, float y, float width, float height, const std::string& label)
		: Widget(x, y, width, height), label(label) 
	{
		_shader = Shader("assets/shaders/OrthoShader.vs", "assets/shaders/OrthoShader.fs");

		
		_quad2D[0] = glm::vec2(0, 1);
		_quad2D[1] = glm::vec2(0, 0);
		_quad2D[2] = glm::vec2(1, 1);
		_quad2D[3] = glm::vec2(1, 0);

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
	}

	void Draw(int screenWidth, int screenHeight) override {
		if (!is_visible) return;

		_screenWidth = _screenWidth;
		_screenHeight = _screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);

		_shader.use();
		_shader.setMat4("projection", _orthoMatrix);
		glm::mat4 model = glm::mat4(1.0);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, screenHeight - position.y - size.y, 1));
		model = glm::scale(model, glm::vec3(size.x, size.y, 1));

		_shader.setMat4("model", model);
		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
	}

	// Handle input and trigger the OnClick event if needed
	void HandleInput(float mouseX, float mouseY, bool mousePressed) override {
		// Check if the mouse is inside the button
		if (mouseX >= position.x && mouseX <= position.x + size.x &&
			mouseY >= position.y && mouseY <= position.y + size.y) {
			if (mousePressed) {
				if (onClick) {
					onClick();  // Invoke the assigned callback
				}
			}
		}
	}

	void SetOnClick(std::function<void()> callback) {
		onClick = callback;
	}

private:
	std::string label;
	std::function<void()> onClick;

	Shader _shader;
	int _screenWidth = 0;
	int _screenHeight = 0;
	glm::mat4 _orthoMatrix;
	glm::vec2 _quad2D[4];
	unsigned int _VBO = 0;
	unsigned int _VAO = 0;
};