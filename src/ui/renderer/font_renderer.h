#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <map>

#include "../../Shader.h"

struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

class FontRenderer {
public:
	FontRenderer();

	~FontRenderer();

	bool LoadFont(const std::string& fontPath, unsigned int fontSize);
	void RenderText(Shader shader, std::string text, glm::vec2 position, float scale, glm::vec3 color);
	void UpdateProjectionMatrix(float screenWidth, float screenHeight);
	const std::map<GLchar, Character>& GetCharacters();

private:
	FT_Library _freeFontLib;
	std::map<GLchar, Character> _characters;
	unsigned int text_vao = 0;
	unsigned int text_vbo = 0;
	glm::mat4 projectionMatrix;

	float screenWidth, screenHeigth;

	float CalculateTextHeight(std::string text, float scale);

	void LoadGlyphs(FT_Face face) {
		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
			std::cerr << "ERROR::FREETYPE: Failed to load glyph" << std::endl;
		} else {
			// set size to load glyphs as
			FT_Set_Pixel_Sizes(face, 0, 24);

			// disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// load first 128 characters of ASCII set
			for (unsigned char c = 0; c < 128; c++) {
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// generate texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<unsigned int>(face->glyph->advance.x)
				};
				_characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
};