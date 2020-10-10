#pragma once
#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class ShaderProgram final
	{
		// Flag if Shaders is compiled
		bool isCompiled = false;
		// Id of the shader program
		GLuint id = 0;

		//Create Shader from source code. if success return 1. return ShaderID via out_shaderID
		bool CreateShader(std::string const& source, GLenum const& shader_type, GLuint & out_shaderID) const noexcept;


	public:
		ShaderProgram()									= delete;
		ShaderProgram(ShaderProgram const&)				= delete;
		ShaderProgram& operator= (ShaderProgram const&) = delete;
		ShaderProgram(ShaderProgram&&)				noexcept;
		ShaderProgram& operator= (ShaderProgram&&)	noexcept;
		~ShaderProgram();
		// Create sheder program with vertex and flagment sheders. Has state IsCompiled()
		ShaderProgram(std::string const& vertex_shader, std::string const& fragment_shader) noexcept;

		// Check if Program in the appropriate state
		bool IsCompiled() const noexcept;
		// Drawing
		bool use() const noexcept;
	};

};