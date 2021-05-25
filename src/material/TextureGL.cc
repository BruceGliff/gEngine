#include "../debug/debug.h"

#include "TextureGL.h"
#include "../renderer/ShaderProgram.h"

#include <glad/glad.h>

#include <iostream>
#include <filesystem>

using namespace Material;

TextureGL::TextureGL(   std::filesystem::path const& Path,
                        aiTextureType TextureType,
                        unsigned /* GLenum */ Filter,
                        unsigned /* GLenum */ WrapMode) noexcept
    : m_Texture{Path}
    , m_TextureType{TextureType} {

    prepairTexture(Filter, WrapMode);
}

void TextureGL::prepairTexture(unsigned Filter, unsigned WrapMode) noexcept {
    int TextureMode = 0;
    switch (m_Texture().Channels) {
        case 4: {
            TextureMode = GL_RGBA;
            break;
        }
        case 3: {
            TextureMode = GL_RGB;
            break;
        }
        default: {
            TextureMode = GL_RGB;
            break;
        }
    }

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, TextureMode, m_Texture().Width,
                                                m_Texture().Height,
                                                0, TextureMode, GL_UNSIGNED_BYTE, m_Texture().Data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapMode);
    glGenerateMipmap(GL_TEXTURE_2D);

    m_Texture.Release();
}

TextureGL::~TextureGL() {
    glDeleteTextures(1, &m_ID);
}

void TextureGL::activateTexture(int TexOffset, Renderer::ShaderProgram const& Shader)
{
    // For texture naming: diffuse_textureN .. for each mesh(model?)
    static int DiffuseCount = 1;
    static int SpecularCount = 1;

    // TexOffset == 0 means that new mesh starts drawing and counting should restart
    if (!TexOffset) {
        DiffuseCount = 1;
        SpecularCount = 1;
    }

    glActiveTexture(GL_TEXTURE0 + TexOffset); // activate proper texture unit before binding
                                              // retrieve texture number (the N in diffuse_textureN)

    std::string name;
    switch (m_TextureType) {
        case aiTextureType_SPECULAR: {
            name = std::string{ "texture_specular" + std::to_string(SpecularCount++) };
            break;
        }
        case aiTextureType_DIFFUSE: {
            name = std::string{ "texture_diffuse" + std::to_string(DiffuseCount++) };
            break;
        }
    default:
        gWARNING("Should not be happen while texture drawing!");
    }


    Shader.SetInt(name.c_str(), TexOffset);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}