#pragma once

#include "raw_texture.h"

namespace std {
    namespace filesystem {
        class path;
    } // namespace filesystem
} // namespace std
namespace Renderer {
    class ShaderProgram;
} // namespace Renderer

namespace Material {

class Texture final {
    raw_texture m_Texture {};

    unsigned m_ID {0};

    // loads texture on GPU
    void prepairTexture(unsigned /* GLenum */ Filter,
                        unsigned /* GLenum */ WrapMode) noexcept; // if it is failed - just terminate
public:

    Texture() = default;
    Texture(TextureGL const&)             = delete;
    Texture(TextureGL&&)                  = delete;
    Texture& operator=(TextureGL const&)  = delete;
    Texture& operator=(TextureGL&&)       = delete;

    Texture(  std::filesystem::path const& Path,
                unsigned /* GLenum */ Filter /* = GL_LINEAR */ ,
                unsigned /* GLenum */ WrapMode /* = GL_CLAMP_TO_EDGE */) noexcept;

    ~Texture();
};

} // namespace Material