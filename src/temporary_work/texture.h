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
    //raw_texture m_Texture {};

    unsigned m_ID {0};

    // loads texture on GPU
    void prepairTexture(unsigned /* GLenum */ Filter,
                        unsigned /* GLenum */ WrapMode) noexcept {}; // if it is failed - just terminate
public:

    Texture() = default;
    Texture(Texture const&)             = delete;
    Texture(Texture&&)                  = delete;
    Texture& operator=(Texture const&)  = delete;
    Texture& operator=(Texture&&)       = delete;

    Texture(  std::filesystem::path const& Path,
                unsigned /* GLenum */ Filter /* = GL_LINEAR */ ,
                unsigned /* GLenum */ WrapMode /* = GL_CLAMP_TO_EDGE */) noexcept {std::cout << "decoy " << Path.string() << "\n";};

    ~Texture() {};

    int dump() { return 4;}
};

} // namespace Material