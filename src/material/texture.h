#pragma once

#include "raw_texture.h"

#include <glad/glad.h>

namespace std {
    namespace filesystem {
        class path;
    } // namespace filesystem
} // namespace std
namespace Renderer {
    class ShaderProgram;
} // namespace Renderer

namespace MaterialNS {

class Texture final {
    unsigned m_ID {};
    void prepairTexture(raw_texture const &, GLenum, GLenum);

public:

    Texture() noexcept;
    Texture(Texture const&)             = delete;
    Texture(Texture&&)                  = delete;
    Texture& operator=(Texture const&)  = delete;
    Texture& operator=(Texture&&)       = delete;

    Texture(std::filesystem::path const& Path,
            GLenum Filter,
            GLenum WrapMode) noexcept; //if it fails - just terminate

    ~Texture();

    void activate(std::string const & prefix, unsigned offset, Renderer::ShaderProgram const& Shader) const;
};

} // namespace Material