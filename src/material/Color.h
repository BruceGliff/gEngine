#pragma once

#include <cstring>
#include <ostream>

namespace Material {

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
    Color(Color const & other) noexcept
        : Color {other.m_color.data}
    {}
    Color(Color && other) noexcept
        : Color {other.m_color.data}
    {}
    Color & operator=(Color const & other) noexcept {
        std::memcpy(m_color.data, other.m_color.data, sizeof(m_color));
        return *this;
    }
    Color & operator=(Color && other) noexcept {
        std::memcpy(m_color.data, other.m_color.data, sizeof(m_color));
        return *this;
    }

    // Construct Color by given components in range 0..1
    Color(float r, float g, float b, float a) {
        auto inRange = [](float x) -> float {
            x = x < 0 ? -x : x;
            x = x > 255.f ? 255.f : x;
            return x <= 1.f ? x : x / 255.f; 
        };
        m_color.r = inRange(r);
        m_color.g = inRange(g);
        m_color.b = inRange(b);
        m_color.a = inRange(a);
    }
    // Construct Color by given components represented as color in range 0..255
    Color(uchar r, uchar g, uchar b)
        : Color {static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f, 1.f} {}
    // Construct Color by given array
    // It is essential to use data with at least 16byte width
    Color(float const * data) {
        std::memcpy(m_color.data, data, sizeof(m_color));
    }
    // Construct Color by given array
    // lenght of data array can be less 4 floats
    Color(float const * data, unsigned size) {
        size = size > 4 ? 4 : size;
        std::memcpy(m_color.data, data, size * sizeof(float));
    }

    friend std::ostream & operator<<(std::ostream & os, Color const & color) {
        os << "Color: [" << color.m_color.r << ", " << color.m_color.g << ", " << color.m_color.b << ", " << color.m_color.a << "]";
        return os;
    }
};



} // namespace Material