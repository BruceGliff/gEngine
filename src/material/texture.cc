#include "../debug/debug.h"

#include "texture.h"
#include "../renderer/ShaderProgram.h"
#include "../manager/ResourceManager.h"

#include <filesystem>

using namespace MaterialNS;

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

void Texture::activate(std::string const & prefix, unsigned offset, Renderer::ShaderProgram const& Shader) const {
    glActiveTexture(GL_TEXTURE0 + offset);  // activate proper texture unit before binding
                                            // retrieve texture number (the N in diffuse_textureN)
    // prefix is Tex_Diffuse, Tex_Specular and so one..
    Shader.SetInt(prefix, offset); // TODO it should be done once!?
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
