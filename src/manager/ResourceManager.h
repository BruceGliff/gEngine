#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

// For unique_ptr
#include "debug/debug.h"
#include "renderer/TextureGL.h"
#include "renderer/ShaderProgram.h"
#include "model/mesh_base.h"

namespace Renderer
{
	enum class ETextureType;
}


// to use unordered_map<filesystem::path, ...>
namespace std {
	template <>
	struct hash<std::filesystem::path>
	{
		std::size_t operator()(std::filesystem::path const& k) const
		{
			return std::filesystem::hash_value(k);
		}
	};
}

namespace Resources
{
	// constains shaders, textures
	class ResourcesManager final
	{
		// TODO make ordering or/and access via name and path?
		// Map of the shaders programs
		typedef std::unordered_map<std::string, std::unique_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
		ShaderProgramsMap shaderPrograms;

		// Map of the textures
		typedef std::unordered_map<std::filesystem::path, std::unique_ptr<Renderer::TextureGL>> TexturesMap;
		TexturesMap textures;
		// Map of models
		typedef std::unordered_map<std::string, std::unique_ptr<Model::IModel>> ModelMap;
		ModelMap models;

		// Path to executable file
		std::filesystem::path const path_to_exec;

		// reads file from res/ directory fe: readFile(res/shaders/fragment.glsl);
		std::string readFile(std::filesystem::path const& relativePath) const;

		// loads model
		template <typename T>
		Model::IModel * loadMesh(std::string const & modelName, std::filesystem::path const& relevantPath);
		// loads primitives
		template <typename T, typename ... Args>
		Model::IModel * loadPrimitive(Args && ... args);

	public:
		ResourcesManager() = delete;
		ResourcesManager(ResourcesManager const&) = delete;
		ResourcesManager(ResourcesManager&&) = delete;
		ResourcesManager& operator=(ResourcesManager const&) = delete;
		ResourcesManager& operator=(ResourcesManager&&) = delete;

		// Lots of copy
		ResourcesManager(std::filesystem::path const& execPath);

		// Compile shader program with shaderName from the sources - vertexPath and fragmentPath
		Renderer::ShaderProgram * loadShaders(	std::string const& shaderProgramName,
												std::filesystem::path const& vertexPath,
												std::filesystem::path const& fragmentPath);
		// Return ShaderProgram by name or nullptr if it did not find (map<>.find() may throw an exception?>
		Renderer::ShaderProgram * getShaderProgram(std::string const& shaderProgramName) const noexcept;

		// TODO make texture unique by path
		// Load texture
		Renderer::TextureGL * loadTexture(std::filesystem::path const& relevantPath, Renderer::ETextureType texType );
		// Load default error texture
		Renderer::TextureGL * loadTexture();
		
		// Loads promitives or model3d depends on type T
		template<typename T, typename ... Args>
		Model::IModel * loadModel(Args && ... args);

		// Gets model by name. Return null if not found
		Model::IModel * getModel(std::string const& name) const noexcept;

		// Returns texture by name or nullptr if it did not find
		Renderer::TextureGL * getTexture(std::string const& textureName) const noexcept;

		std::filesystem::path const& getPathToExucutable() const;

	};
}

#include "ResourceManager.hpp"
