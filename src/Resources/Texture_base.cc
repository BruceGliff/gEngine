#include "Texture_base.h"

#include "stb_image.h"
#include <iostream>
#include <exception>

#include <fstream>

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

    std::ofstream ppm{ "C:\\Code\\gEngine\\out.ppm" };
    ppm << "P6\n" << width << " " << height << "\n255\n";
    ppm.write(reinterpret_cast<char const*>(data), height * width * channels);
    
}

Resources::Texture_base::~Texture_base()
{
    if (!isError)
        stbi_image_free(data);
}
