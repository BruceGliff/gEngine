#include "debug/debug.h"

#include "raw_texture.h"

#include "../process/global.h"
#include "../manager/ResourceManager.h"

#include <iostream>
#include <fstream>

#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Material;

raw_texture::raw_texture(std::filesystem::path const& path) noexcept {
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

void raw_texture::generateErrorTexture() noexcept {
    if (!isNoNeedToDelete) {
        Release();
    }
    data = whiteErrorTexture;
    width = 2;
    height = 1;
    channels = 3;
    isNoNeedToDelete = true;
}

void raw_texture::Release() noexcept {
    if (isNoNeedToDelete)
        return;

    stbi_image_free(data);
    isNoNeedToDelete = true;
}

raw_texture::~raw_texture() {
    Release();
}

void raw_texture::DumpTexture() const {
    static unsigned idx = 0;
    static std::filesystem::path const & exPath = GLOBAL::GetResManager().getPathToExucutable();
    std::ofstream ppm{exPath / std::string{"out[" + std::to_string(idx++) + "]"}, std::ios::binary };
    ppm << "P6\n" << width << ' ' << height << '\n' << 255 << std::endl;
    for (int i = 0; i != height; ++i) {
        for (int j = 0; j != width; ++j) {
            ppm.write(reinterpret_cast<char*>(data + (i * width + j) * channels), 3);
        }
    }
    ppm.close();
}
