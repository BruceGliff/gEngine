#include "debug/debug.h"

#include "Texture_base.h"

#include <iostream>

#include <fstream>
#include <filesystem>

#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Resources::Texture_base::Texture_base(std::filesystem::path const& path) noexcept
{
    // Load texture upside down
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        gWARNING(std::string{ "Can not load texture: " } + path.string());
        generateErrorTexture();
    }
    isNoNeedToDelete = false;
}
Resources::Texture_base::Texture_base() noexcept {
    generateErrorTexture();
}

void Resources::Texture_base::generateErrorTexture() noexcept {
    if (!isNoNeedToDelete) {
        Release();
    }
    data = whiteErrorTexture;
    width = 2;
    height = 1;
    channels = 3;
    isNoNeedToDelete = true;
}

void Resources::Texture_base::Release() noexcept
{
    if (isNoNeedToDelete)
        return;

    stbi_image_free(data);
    isNoNeedToDelete = true;
}

Resources::Texture_base::~Texture_base()
{
    if (!isNoNeedToDelete)
        Release();
}

void Resources::Texture_base::DumpTexture() const
{
    std::ofstream ppm{ "C:\\Code\\gEngine\\out.ppm", std::ios::binary };
    ppm << "P6" << std::endl << width << " " << height << std::endl << 255 << std::endl;
    for (int i = 0; i != height; ++i)
        for (int j = 0; j != width; ++j)
        {
            ppm.write(reinterpret_cast<char*>(data + (i * width + j) * channels), 3);
        }
    ppm.close();
}
