#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include "../ui_manager.h"

#include "../../../Shader.h"

class TextLabel {
public:
	TextLabel(UIManager* uiManager, FontManager& fontManager)
		: uiManager(uiManager), _characters(fontManager.GetCharacters())
	{
		Initialize();
		text_shader = Shader("assets/shaders/textShader.vs", "assets/shaders/textShader.fs");
	}

	float CalculateTextHeight(std::string text, float scale) {
		float maxHeight = 0.0f;
		for (char c : text) {
			Character ch = _characters[c];
			float characterHeight = ch.Size.y * scale; // Calculate character height with scale

			if (characterHeight > maxHeight)
				maxHeight = characterHeight;
		}
		return maxHeight; // Return the maximum height found
	}

	void Render(float screenWidth, float screenHeight, std::string text, float x, float y, float scale, glm::vec3 color) {
		float textHeight = CalculateTextHeight(text, scale); // Calculate the height of the text
		float offsetY = textHeight; // Offset the y position by the height of the text

		text_shader.use();
		//text_shader.setMat4("projection", uiManager->GetProjectionMatrix());
		//text_shader.setMat4("projection", glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f)); // Top-left origin
		text_shader.setMat4("projection", glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight));

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
		for (c = text.begin(); c != text.end(); c++) {
			Character ch = _characters[*c];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = screenHeight - y - (ch.Size.y - ch.Bearing.y) * scale - offsetY;

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

private:
	bool Initialize() {
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
	
	float x, y, scale;
	unsigned int text_vao = 0;
	unsigned int text_vbo = 0;
	std::string text;
	glm::vec3 color;
	std::map<GLchar, Character> _characters;
	Shader text_shader;
	UIManager* uiManager;
};