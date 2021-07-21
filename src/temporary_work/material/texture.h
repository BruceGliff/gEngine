#pragma once

#include "raw_texture.h"

#include <iostream>
#include <filesystem>

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
    unsigned m_ID {};

public:

    Texture() = default;
    Texture(Texture const&)             = delete;
    Texture(Texture&&)                  = delete;
    Texture& operator=(Texture const&)  = delete;
    Texture& operator=(Texture&&)       = delete;

    Texture(  std::filesystem::path const& Path,
                unsigned /* GLenum */ Filter /* = GL_LINEAR */ ,
                unsigned /* GLenum */ WrapMode /* = GL_CLAMP_TO_EDGE */) noexcept; //if it fails - just terminate

    ~Texture();

    void activateTexture(std::string const & prefix, int offset/*,  Shader*/);
};

} // namespace Material