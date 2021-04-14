#pragma once

#include "mesh_base.h"

#include <filesystem>

#include <assimp/scene.h>

namespace Model {
	// TODO check for virtual ~Model(MEsh)
	class Model3D : public IModel
	{
		std::vector<Mesh> m_meshes;
		std::filesystem::path m_directory_path;
		
		void loadModel(std::filesystem::path const& path);
		void processNode(aiNode* node, aiScene const * scene);
		Mesh processMesh(aiMesh* mesh, aiScene const* scene);
		std::vector<Renderer::TextureGL*> loadMaterialTextures(aiMaterial* mat, aiTextureType type);

	public:
		Model3D(std::filesystem::path const& path);
		void Draw(Renderer::ShaderProgram const & shader) const override;

	};
}