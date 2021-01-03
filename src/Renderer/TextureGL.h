#pragma once

#include "glad/glad.h"
#include "../texture/Texture_base.h"

namespace Renderer
{
	// Loader texture in GPU
	class TextureGL final : public Resources::Texture_base
	{
		GLuint ID = 0;
		int const GLindicies_begin = GL_TEXTURE0;
		int slotID = 0;

	public:
		TextureGL()									= delete;
		TextureGL(TextureGL const&)					= delete;
		TextureGL(TextureGL&&)						= delete;
		TextureGL& operator=(TextureGL const&)		= delete;
		TextureGL& operator=(TextureGL&&)			= delete;

		TextureGL(std::filesystem::path const& path, GLenum const filter = GL_LINEAR, GLenum const wrapMode = GL_CLAMP_TO_EDGE) noexcept;
		~TextureGL();
		// Make this texture active
		void bind() const noexcept;
		// Disable active texture
		static void unbind() noexcept;

	};
}