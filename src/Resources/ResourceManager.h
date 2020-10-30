#pragma once

#include <memory>
#include <unordered_map>
#include <string>
// TODO it SINGLTONE!

namespace Renderer
{
	class ShaderProgram;
	class TextureGL;
}

namespace Resources
{
	class ResourcesManager final
	{
		// Map of the saders programs
		typedef std::unordered_map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
		ShaderProgramsMap shaderPrograms;

		// Map of the textures
		typedef std::unordered_map<std::string, std::shared_ptr<Renderer::TextureGL>> TexturesMap;
		TexturesMap textures;

		// Path to executable file
		std::string const path;

		// Calculate path of the res/ directory. Throws run_time exception if errors occured
		std::string computePath(std::string const & path) const;
		// Get file from res/ directory fe: getFile(res/shaders/fragment.glsl);
		std::string getFile(std::string const& relativePath) const;


	public:
		ResourcesManager()										= delete;
		ResourcesManager(ResourcesManager const &)				= delete;
		ResourcesManager(ResourcesManager&&)					= delete;
		ResourcesManager& operator=(ResourcesManager const&)	= delete;
		ResourcesManager& operator=(ResourcesManager&&)			= delete;

		ResourcesManager(std::string const& execPath);

		// Compile shader program with shaderName from the sources - vertexPath and fragmentPath
		std::shared_ptr <Renderer::ShaderProgram> loadShaders(	std::string const & shaderProgramName,
																std::string const & vertexPath,
																std::string const & fragmentPath);
		// Return ShaderProgram by name or nullptr if it did not find (map<>.find() may throw an exception?>
		std::shared_ptr <Renderer::ShaderProgram> getShaderProgram(std::string const& shaderProgramName) const noexcept;

		// Load texture
		std::shared_ptr <Renderer::TextureGL> loadTexture(std::string const& textureName, std::string const & relevantPath);
		// Return texture by name or nullptr if it did ont find
		std::shared_ptr <Renderer::TextureGL> getTexture(std::string const& textureName) const noexcept;
	};
}