#pragma once

#include <string>

namespace Resources
{
	// Implementation of the texture as the raw data of pixels
	class Texture_base
	{
		bool isError = false;
		unsigned char whiteErrorTexture[2] = { 0, 0 };
	protected:
		unsigned char* data = 0;
		int channels = 0;
		int width = 0;
		int height = 0;
	public:
		Texture_base()									= delete;
		Texture_base(Texture_base const&)				= delete;
		Texture_base(Texture_base&&)					= delete;
		Texture_base& operator=(Texture_base const&)	= delete;
		Texture_base& operator=(Texture_base&&)			= delete;

		Texture_base(std::string const& relevantPath) noexcept;
		virtual ~Texture_base();
	};
}