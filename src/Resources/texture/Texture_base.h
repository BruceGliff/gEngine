#pragma once

#include <string>

namespace Resources
{
	// Implementation of the texture as the raw data of pixels
	class Texture_base
	{
		bool isError = false;
		unsigned char whiteErrorTexture[3] = { 255, 255, 255 };
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

		// Out texture in .ppm format. Without alpha. with name: out.ppm
		void DumpTexture() const;
	};
}