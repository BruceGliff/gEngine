#include "Texture_base.h"

#include "stb_image.h"
#include <iostream>
#include <exception>

#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Resources::Texture_base::Texture_base(std::string const& path) noexcept
{
    // Load texture upside down
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(std::string{path}.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        std::cerr << "ERROR:: run-time:\n" << "Can not load texture: " << path;
        data = whiteErrorTexture;
        isError = true;
    }
}

Resources::Texture_base::~Texture_base()
{
    if (!isError)
        stbi_image_free(data);
}
