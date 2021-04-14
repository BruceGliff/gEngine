#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>

// TODO This is just from tutorial for testing
// Make it on your way


// forward delaration
namespace Renderer {
	class ShaderProgram;
	class TextureGL;
}

namespace Model
{	
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coord;
	};

	class IModel {
	protected:
		IModel() {}
	public:
		virtual void Draw(Renderer::ShaderProgram const & shader) const = 0;
		virtual ~IModel() {}
	};

	class Mesh
	{
		unsigned int VAO, VBO, EBO;
		
		void setupMesh();

	public:
		Mesh(std::vector<Vertex> const & vertices, std::vector<unsigned int> const & indices, std::vector<Renderer::TextureGL*> const & textures);
		void Draw(Renderer::ShaderProgram const & shader) const;

	public:
		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Renderer::TextureGL*>	m_textures;
	};

}