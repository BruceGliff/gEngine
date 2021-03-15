#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <assimp/scene.h>

// TODO This is just from tutorial for testing
// Make it on your way


// forward delaration
namespace Renderer
{
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

	typedef std::shared_ptr<Renderer::TextureGL> type_pTextures;
	class Mesh
	{
		unsigned int VAO, VBO, EBO;
		
		void setupMesh();

	public:
		Mesh(std::vector<Vertex> const & vertices, std::vector<unsigned int> const & indices, std::vector<type_pTextures> const & textures);
		void Draw(Renderer::ShaderProgram const & shader);

	public:
		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<type_pTextures>	m_textures;
	};
	// TODO check for virtual ~Model(MEsh)
	class Model
	{
		std::vector<Mesh> m_meshes;
		std::filesystem::path m_directory_path;
		
		void loadModel(std::filesystem::path const& path);
		void processNode(aiNode* node, aiScene const * scene);
		Mesh processMesh(aiMesh* mesh, aiScene const* scene);
		std::vector<type_pTextures> loadMaterialTextures(aiMaterial* mat, aiTextureType type);

	public:
		Model(std::filesystem::path const& path);
		void Draw(Renderer::ShaderProgram const & shader);

	};
}