#include "debug/debug.h"

#include "raw_texture.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Material;

raw_texture::raw_texture(std::filesystem::path const& Path) noexcept 
    : m_TexName {Path.filename().string()} {
    // Load texture upside down
    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(Path.string().c_str(), &m_Width, &m_Height, &m_Channels, 0);
    
    m_IsNoNeedToDelete = !m_Data;
    if (m_IsNoNeedToDelete) {
        gWARNING(std::string{ "Can not load texture: " } + Path.string());
        generateErrorTexture();
    }
}
raw_texture::raw_texture() noexcept {
    generateErrorTexture();
}

void raw_texture::generateErrorTexture() noexcept {
    // Release data if it has to be released
    Release();
    m_Data = m_WhiteErrorTexture;
    m_Width = 2;
    m_Height = 1;
    m_Channels = 3;
    m_IsNoNeedToDelete = true;
}

void raw_texture::Release() noexcept {
    if (m_IsNoNeedToDelete)
        return;

    stbi_image_free(m_Data);
    m_IsNoNeedToDelete = true;
}

raw_texture::~raw_texture() {
    Release();
}

raw_texture::ret_data const & raw_texture::operator()() const noexcept {
    return m_Return;
}

void raw_texture::DumpTexture() const {
    static unsigned Indx = 0;
    // TODO FIX THIS AFTER RESMGR!
    static std::filesystem::path const & ExPath = "C:\\Code\\gEngine\\build\\bin\\Debug";//GLOBAL::GetResManager().getPathToExucutable();

    std::string const OutFormat{ "out" + std::string{m_IsNoNeedToDelete ? "_error" :  ""} + "_" + m_TexName + "[" + std::to_string(Indx++) + "].ppm"};

    std::ofstream ppm{ExPath / OutFormat, std::ios::binary };
    ppm << "P6\n" << m_Width << ' ' << m_Height << '\n' << 255 << std::endl;
    for (int i = 0; i != m_Height; ++i) {
        for (int j = 0; j != m_Width; ++j) {
            ppm.write(reinterpret_cast<char*>(m_Data + (i * m_Width + j) * m_Channels), 3);
        }
    }
}
