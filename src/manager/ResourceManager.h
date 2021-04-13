#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

// For unique_ptr
#include "renderer/ShaderProgram.h"
#include "renderer/TextureGL.h"
#include "model/primitives.h"
#include "debug/debug.h"

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

		// read file from res/ directory fe: readFile(res/shaders/fragment.glsl);
		std::string readFile(std::filesystem::path const& relativePath) const;

		template <typename T>
		Model::IModel * load(std::string const & modelName, std::filesystem::path const& relevantPath) {
			ModelMap::const_iterator it = models.find(modelName);
			// if model does not exist, then load it
			if (it == models.end()) {
				return models.emplace(modelName, std::make_unique<T>(path_to_exec / relevantPath)).first->second.get();
			}
			
			// if model already exists, return it
			return it->second.get();
		}
		template <typename T>
		Model::IModel * load(std::vector<Renderer::TextureGL *> const & textures = {})
		{
			// We assume that type has to be a primitive
			if (!std::is_base_of<Model::Primitive, T>::value)
			{
				gWARNING(std::string{"Type is not a primitive: "} + typeid(T).name());
				return nullptr;
			}
			std::string const modelName = typeid(T).name();
			ModelMap::const_iterator it = models.find(typeid(T).name());
			if (it == models.end()) {
				T * p = new T{textures};
				Model::IModel * pM = dynamic_cast<Model::IModel *>(p);	
				if (!pM) {
					delete p;
					gWARNING(std::string{"This is not suppose to happen: Check with typeid() gave wrong result!\n "} + typeid(T).name());
					return nullptr;
				}
				return models.emplace(modelName, pM).first->second.get();
			}
			return it->second.get();
		}

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
		
		// Load promitives
		template<typename T, typename ... Args>
		Model::IModel * loadModel(Args && ... args)
		{
			return load<T>(args ...);
		}
		// Get model by name. Return null if not found
		Model::IModel * getModel(std::string const& name) const noexcept;

		// Return texture by name or nullptr if it did ont find
		Renderer::TextureGL * getTexture(std::string const& textureName) const noexcept;

		std::filesystem::path const& getPathToExucutable() const;

	};
}