#include "font_renderer.h"
#include <glad/glad.h>

FontRenderer::FontRenderer() {
	if (FT_Init_FreeType(&_freeFontLib)) {
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	glGenVertexArrays(1, &text_vao);
	glGenBuffers(1, &text_vbo);
	glBindVertexArray(text_vao);
	glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

FontRenderer::~FontRenderer() {
	FT_Done_FreeType(_freeFontLib);
}

bool FontRenderer::LoadFont(const std::string& fontPath, unsigned int fontSize) {
	FT_Face face;
	if (FT_New_Face(_freeFontLib, fontPath.c_str(), 0, &face)) {
		std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);
	LoadGlyphs(face);
	FT_Done_Face(face);
	return true;
}

float FontRenderer::CalculateTextHeight(std::string text, float scale) {
	float maxHeight = 0.0f;
	for (char c : text) {
		Character ch = _characters[c];
		float characterHeight = ch.Size.y * scale; // Calculate character height with scale

		if (characterHeight > maxHeight)
			maxHeight = characterHeight;
	}
	return maxHeight; // Return the maximum height found
}

void FontRenderer::UpdateProjectionMatrix(float screenWidth, float screenHeight) {
	projectionMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight); // Top-left origin
	this->screenWidth = screenWidth;
	this->screenHeigth = screenHeight;
}

void FontRenderer::RenderText(Shader shader, std::string text, glm::vec2 position, float scale, glm::vec3 color) {
	float textHeight = CalculateTextHeight(text, 1); // Calculate the height of the text
	float offsetY = textHeight; // Offset the y position by the height of the text

	shader.use();
	//text_shader.setMat4("projection", uiManager->GetProjectionMatrix());
	//text_shader.setMat4("projection", glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f)); // Top-left origin
	shader.setMat4("projection", projectionMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// activate corresponding render state	
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text_vao);

	// iterate through all characters
	std::string::const_iterator c;

	float x = position.x;
	float y = position.y;

	for (c = text.begin(); c != text.end(); c++) {
		Character ch = _characters[*c];

		float xpos = x + ch.Bearing.x * 1;
		float ypos = screenHeigth - y - (ch.Size.y - ch.Bearing.y) * scale - offsetY;

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

const std::map<GLchar, Character>& FontRenderer::GetCharacters() { return _characters; }