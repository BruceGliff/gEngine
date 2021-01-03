#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

// TODO This is just from tutorial for testing
// Make it on your way


// forward delaration
namespace Renderer
{
	class ShaderProgram;
}
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

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
		std::string path; // to future optimize if it has been loaded already
	};

	class Mesh
	{
		unsigned int VAO, VBO, EBO;

		void setupMesh();

	public:
		Mesh(std::vector<Vertex> const & vertices, std::vector<unsigned int> const & indices, std::vector<Texture> const & textures);
		void Draw(Renderer::ShaderProgram& shader);

	public:
		std::vector<Vertex>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Texture>		m_textures;
	};

	class Model
	{
		std::vector<Mesh> m_meshes;
		std::filesystem::path m_directory_path;
		
		void loadModel(std::filesystem::path const& path);
		void processNode(aiNode* node, aiScene const * scene);
		Mesh processMesh(aiMesh* mesh, aiScene const* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string const& typeName);

	public:
		Model(std::filesystem::path const& path);
		void Draw(Renderer::ShaderProgram& shader);

	};
}