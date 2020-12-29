#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <iostream>
#include <vector>
#include <string>

// TODO This is just from tutorial for testing
// Make it on your way


// forward delaration
namespace Renderer
{
	class ShaderProgram;
}

namespace Model
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coord;
	};

	struct Texture
	{
		unsigned int id;
		std::string type; // diffuse, specular ...
	};

	class Mesh
	{
		unsigned int VAO, VBO, EBO;

		void setupMesh();

	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Draw(Renderer::ShaderProgram& shader);

	public:
		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Texture>		m_textures;
	};
}