#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "../Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
private:
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indicesCount);
	Mesh(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indicesCount, Texture textures[], size_t textureCount);
	void Draw(Shader& shader);

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};