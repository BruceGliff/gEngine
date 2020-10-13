#include "Texture_base.h"

#include "stb_image.h"
#include <iostream>
#include <exception>

#include <fstream>

#define STBI_ONLY_PNG
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
        width = 1;
        height = 1;
        channels = 3;
        isError = true;
    }
}

Resources::Texture_base::~Texture_base()
{
    if (!isError)
        stbi_image_free(data);
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
