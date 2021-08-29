#pragma once

#include "raw_texture.h"

#include <string_view>

#include <glad/glad.h>

namespace std {
    namespace filesystem {
        class path;
    } // namespace filesystem
} // namespace std
namespace NSRenderer {
    class ShaderProgram;
} // namespace Renderer

namespace NSMaterial {

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

    void activate(char const * prefix, unsigned offset, NSRenderer::ShaderProgram const& Shader) const;
};

class TextureCube final {
    unsigned m_ID {};
    void prepairTexture(std::filesystem::path const & FolderWithTextures);

public:
    // Loads Cube texture from Folder. /textures/Ocean/*.jpg
    // Naming "right", "left", "top", "bottom" etc will be added automaticaly
    TextureCube(std::filesystem::path const & FolderWithTextures);

    TextureCube() = delete;
    TextureCube(TextureCube const&)             = delete;
    TextureCube(TextureCube&&)                  = delete;
    TextureCube& operator=(TextureCube const&)  = delete;
    TextureCube& operator=(TextureCube&&)       = delete;

    ~TextureCube();

    void activate(NSRenderer::ShaderProgram const& Shader) const;
};

} // namespace NSMaterial