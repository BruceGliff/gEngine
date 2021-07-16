
#include "texture.h"

//#include <glad/glad.h>

#include <iostream>
#include <filesystem>

using namespace Material;

Texture::Texture(   std::filesystem::path const& Path,
                    unsigned /* GLenum */ Filter,
                    unsigned /* GLenum */ WrapMode) noexcept {

    raw_texture texture_data{Path};

    int TextureMode = 0;
    switch (texture_data().Channels) {
        case 4: {
            TextureMode = 4;//GL_RGBA;
            break;
        }
        case 3: {
            TextureMode = 3;//GL_RGB;
            break;
        }
        default: {
            TextureMode = 3;//GL_RGB;
            break;
        }
    }
/*
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
*/
    texture_data.DumpTexture();
}

Texture::~Texture() {
    //glDeleteTextures(1, &m_ID);
}

void Texture::activateTexture(std::string const & prefix, int offset) {
    // do!
}

// void TextureGL::activateTexture(int TexOffset, Renderer::ShaderProgram const& Shader)
// {
//     // For texture naming: diffuse_textureN .. for each mesh(model?)
//     static int DiffuseCount = 1;
//     static int SpecularCount = 1;

//     // TexOffset == 0 means that new mesh starts drawing and counting should restart
//     if (!TexOffset) {
//         DiffuseCount = 1;
//         SpecularCount = 1;
//     }

//     glActiveTexture(GL_TEXTURE0 + TexOffset); // activate proper texture unit before binding
//                                               // retrieve texture number (the N in diffuse_textureN)

//     std::string name;
//     switch (m_TextureType) {
//         case aiTextureType_SPECULAR: {
//             name = std::string{ "texture_specular" + std::to_string(SpecularCount++) };
//             break;
//         }
//         case aiTextureType_DIFFUSE: {
//             name = std::string{ "texture_diffuse" + std::to_string(DiffuseCount++) };
//             break;
//         }
//     default:
//         gWARNING("Should not be happen while texture drawing!");
//     }


//     Shader.SetInt(name.c_str(), TexOffset);
//     glBindTexture(GL_TEXTURE_2D, m_ID);
// }