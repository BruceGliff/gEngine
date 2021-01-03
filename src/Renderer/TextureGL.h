#pragma once

#include "glad/glad.h"
#include "../texture/Texture_base.h"


namespace Renderer
{
	enum class ETextureType
	{
		SPECULAR,
		DIFFUSE
		// ...
	};
	
	class ShaderProgram;

	// Loader texture in GPU
	// This class not in Resources NS as it is not loaded in RAM
	class TextureGL final : public Resources::Texture_base
	{
		GLuint ID = 0;
		ETextureType texType;

	public:
		TextureGL()									= delete;
		TextureGL(TextureGL const&)					= delete;
		TextureGL(TextureGL&&)						= delete;
		TextureGL& operator=(TextureGL const&)		= delete;
		TextureGL& operator=(TextureGL&&)			= delete;

		TextureGL(std::filesystem::path const& path, ETextureType textureType = ETextureType::DIFFUSE, GLenum const filter = GL_LINEAR, GLenum const wrapMode = GL_CLAMP_TO_EDGE) noexcept;
		~TextureGL();
		
		// activate texture for drawing
		void activateTexture(int texOffset, ShaderProgram const& shader);

	};
}