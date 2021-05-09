#pragma once

#include <string>
#include <filesystem>

namespace Resources
{
	// Implementation of the texture as the raw data of pixels
	class Texture_base
	{
		// flag if data cant be deleted (if errors occures or it has been already deleted)
		bool isNoNeedToDelete = true;
		// if errors occure white texture loads
		unsigned char whiteErrorTexture[6] = { 255, 255, 255, 0, 0, 0};
		void generateErrorTexture() noexcept;
	protected:
		unsigned char* data = 0;
		int channels = 0;
		int width = 0;
		int height = 0;
	public:
		Texture_base() noexcept;
		Texture_base(Texture_base const&)				= delete;
		Texture_base(Texture_base&&)					= delete;
		Texture_base& operator=(Texture_base const&)	= delete;
		Texture_base& operator=(Texture_base&&)			= delete;

		Texture_base(std::filesystem::path const& relevantPath) noexcept;

		// free stored data
		void Release() noexcept;
		virtual ~Texture_base();

		// Out texture in .ppm format. Without alpha. with name: out.ppm
		void DumpTexture() const;
	};
}