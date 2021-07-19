#pragma once

#include <cstring>
#include <ostream>

namespace Renderer {
    class ShaderProgram;
} // namespace Renderer

namespace MaterialNS {

struct Color {
    using uchar = unsigned char;
    // 4 colors: red, green, blue, alpha
    // and data[4] aggregated
    union {
        struct {
            float r,g,b,a;
        };
        float data[4] {};
    } m_color;

    Color() = default;
    Color(Color const & other) noexcept;
    Color(Color && other) noexcept;
    Color & operator=(Color const & other) noexcept;
    Color & operator=(Color && other) noexcept;

    // Construct Color by given components in range 0..1
    Color(float r, float g, float b, float a) noexcept;
    // Construct Color by given components represented as color in range 0..255
    Color(uchar r, uchar g, uchar b) noexcept;
    // Construct Color by given array
    // It is essential to use data with at least 16byte width
    Color(float const * data) noexcept;
    // Construct Color by given array
    // lenght of data array can be less 4 floats
    Color(float const * data, unsigned size) noexcept;

    // Pass color data to shader (TOBEIMPL)
    void activate(std::string const & prefix, unsigned offset, Renderer::ShaderProgram const & shader) const;
};

std::ostream & operator<<(std::ostream & os, Color const & color);


} // namespace Material