#include "../debug/debug.h"

#include "texture.h"
#include "../renderer/ShaderProgram.h"
#include "../manager/ResourceManager.h"

#include <filesystem>

using namespace NSMaterial;

Texture::Texture(   std::filesystem::path const& Path,
                    GLenum Filter,
                    GLenum WrapMode) noexcept {
    prepairTexture(raw_texture{Path}, Filter, WrapMode);
}
// To generate error Texture
Texture::Texture() noexcept {
    // TODO find proper params for error texture
    prepairTexture(raw_texture{}, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

void Texture::prepairTexture(raw_texture const & texture_data,
                            GLenum Filter,
                            GLenum WrapMode) {
    GLint TextureMode {};
    switch (texture_data().Channels) {
        case 4:
            TextureMode = GL_RGBA;
            break;
        case 3:
            TextureMode = GL_RGB;
            break;
        default:
            TextureMode = GL_RGB;
            break;
    }

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, TextureMode, texture_data().Width,
                                                texture_data().Height,
                                                0, TextureMode, GL_UNSIGNED_BYTE, texture_data().Data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapMode);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_ID);
}

void Texture::activate(char const * prefix, unsigned offset, NSRenderer::ShaderProgram const& Shader) const {
    glActiveTexture(GL_TEXTURE0 + offset);  // activate proper texture unit before binding
                                            // retrieve texture number (the N in diffuse_textureN)
    // prefix is _Diffuse, _Specular and so one..
    std::string const name { std::string{"Tex"}.append(prefix) };
    std::string const flag {std::string{"IsTex"}.append(prefix) };
    Shader.SetInt(  std::string{"Material."}.append(prefix).append(".Tex").c_str(),
                    offset); // TODO it should be done once!?
    Shader.SetInt(  std::string{"Material."}.append(prefix).append(".IsTex").c_str(), 
                    1); // TODO it should be done once!?
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

TextureCube::TextureCube(std::filesystem::path const & FolderWithTextures) {
    prepairTexture(FolderWithTextures);
}

void TextureCube::prepairTexture(std::filesystem::path const & FolderWithTextures) {
    char const * Postfix[6] = { 
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);

    // 6 - number of cube's faces.
    // For each face there should be a texture file
    for (int i = 0; i != 6; ++i) {
        raw_texture data {FolderWithTextures / Postfix[i], false};
        glTexImage2D(   GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                        0, GL_RGB, data().Width, data().Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data().Data
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

TextureCube::~TextureCube() {
    glDeleteTextures(1, &m_ID);
}

void TextureCube::activate(NSRenderer::ShaderProgram const& Shader) const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
}
