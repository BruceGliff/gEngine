#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

namespace Renderer
{
	class ShaderProgram;
	class TextureGL;
	enum class ETextureType;
}

namespace Model
{
	class Model;
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
		typedef std::unordered_map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
		ShaderProgramsMap shaderPrograms;

		// Map of the textures
		typedef std::unordered_map<std::filesystem::path, std::shared_ptr<Renderer::TextureGL>> TexturesMap;
		TexturesMap textures;
		// Map of models
		typedef std::unordered_map<std::string, std::shared_ptr<Model::Model>> ModelMap;
		ModelMap models;

		// Path to executable file
		std::filesystem::path const path_to_exec;

		// read file from res/ directory fe: readFile(res/shaders/fragment.glsl);
		std::string readFile(std::filesystem::path const& relativePath) const;


	public:
		ResourcesManager() = delete;
		ResourcesManager(ResourcesManager const&) = delete;
		ResourcesManager(ResourcesManager&&) = delete;
		ResourcesManager& operator=(ResourcesManager const&) = delete;
		ResourcesManager& operator=(ResourcesManager&&) = delete;

		// Lots of copy
		ResourcesManager(std::filesystem::path const& execPath);

		// Compile shader program with shaderName from the sources - vertexPath and fragmentPath
		std::shared_ptr <Renderer::ShaderProgram> loadShaders(	std::string const& shaderProgramName,
																std::filesystem::path const& vertexPath,
																std::filesystem::path const& fragmentPath);
		// Return ShaderProgram by name or nullptr if it did not find (map<>.find() may throw an exception?>
		std::shared_ptr <Renderer::ShaderProgram> getShaderProgram(std::string const& shaderProgramName) const noexcept;

		// TODO make texture unique by path
		// Load texture
		std::shared_ptr <Renderer::TextureGL> loadTexture(std::filesystem::path const& relevantPath, Renderer::ETextureType texType );
		
		// Load model. If model with name already created, then return it. Do not overwrite
		std::shared_ptr <Model::Model> loadModel(std::string const & name, std::filesystem::path const& relevantPath);
		// Get model by name. Return null if not found
		std::shared_ptr <Model::Model> getModel(std::string const& name) const noexcept;

		// Return texture by name or nullptr if it did ont find
		std::shared_ptr <Renderer::TextureGL> getTexture(std::string const& textureName) const noexcept;

		std::filesystem::path const& getPathToExucutable() const;

	};
}