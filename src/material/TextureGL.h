#pragma once

#include "raw_texture.h"
#include "IMatNode.h"

#include <assimp/material.h>

namespace std {
    namespace filesystem {
        class path;
    } // namespace filesystem
} // namespace std
namespace Renderer {
    class ShaderProgram;
} // namespace Renderer

namespace Material {

class TextureGL final
    : IMatNode {
    raw_texture m_Texture {};

    unsigned m_ID {0};
    aiTextureType m_TextureType {aiTextureType_DIFFUSE};

    // loads texture on GPU
    void prepairTexture(unsigned /* GLenum */ Filter,
                        unsigned /* GLenum */ WrapMode) noexcept; // if it is failed - just terminate
public:

    TextureGL() = default;
    TextureGL(TextureGL const&)             = delete;
    TextureGL(TextureGL&&)                  = delete;
    TextureGL& operator=(TextureGL const&)  = delete;
    TextureGL& operator=(TextureGL&&)       = delete;

    TextureGL(  std::filesystem::path const& Path,
                aiTextureType TextureType,
                unsigned /* GLenum */ Filter /* = GL_LINEAR */ ,
                unsigned /* GLenum */ WrapMode /* = GL_CLAMP_TO_EDGE */) noexcept;

    ~TextureGL();
    
    // activate texture for drawing
    void activateTexture(int texOffset, Renderer::ShaderProgram const& shader);




};

} // namespace Material