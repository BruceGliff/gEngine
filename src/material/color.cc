#include "color.h"

#include "../renderer/ShaderProgram.h"

using namespace NSMaterial;

Color::Color(Color const & other) noexcept
    : Color {other.m_color.data} {}
Color::Color(Color && other) noexcept
    : Color {other.m_color.data} {}
Color & Color::operator=(Color const & other) noexcept {
    std::memcpy(m_color.data, other.m_color.data, sizeof(m_color));
    return *this;
}
Color & Color::operator=(Color && other) noexcept {
    std::memcpy(m_color.data, other.m_color.data, sizeof(m_color));
    return *this;
}

Color::Color(float r, float g, float b, float a) noexcept {
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

Color::Color(uchar r, uchar g, uchar b) noexcept
    : Color {static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f, 1.f} {}

Color::Color(float const * data) noexcept {
    std::memcpy(m_color.data, data, sizeof(m_color));
}

Color::Color(float const * data, unsigned size) noexcept {
    size = size > 4 ? 4 : size;
    std::memcpy(m_color.data, data, size * sizeof(float));
}

void Color::activate(char const * prefix, unsigned offset, NSRenderer::ShaderProgram const & Shader) const {
    // TODO activete color
    // prefix is _Diffuse, _Specular and so one..
    // TODO try to get rid of string
    Shader.setVec4( std::string{prefix}.append(".Col").c_str(),
                    glm::vec4{m_color.r,m_color.g,m_color.b,m_color.a}); // TODO it should be done once!?
    Shader.SetInt(  std::string{prefix}.append(".IsTex").c_str(), 
                    0); // TODO it should be done once!?
}


std::ostream & operator<<(std::ostream & os, Color const & color) {
    os << "Color: [" << color.m_color.r << ", " << color.m_color.g << ", " << color.m_color.b << ", " << color.m_color.a << "]";
    return os;
}