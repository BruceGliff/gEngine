// Class represent regular Color4F
#pragma once

#include "IMatNode.h"

namespace Material {

class Color
    : public IMatNode {
public:
    // 4 colors: red, green, blue, alpha
    // and data[4] aggregated
    union {
        struct {
            float r,g,b,a;
        };
        float data[4] {};
    } m_color;


    // Construct Color by given components
    Color(float r, float g, float b, float a = 1.f) {
        m_color.r = r;
        m_color.g = g;
        m_color.b = b;
        m_color.a = a;
    }
    // Construct Color by given array
    // It is essential to use data with at least 16byte width
    Color(float const * data) {
        for (unsigned i = 0; i != 4; ++i) {
            m_color.data[i] = data[i];
        }
    }
    // Construct Color by given array
    // lenght of data array can be less 4 floats
    Color(float const * data, unsigned size) {
        size = size > 4 ? 4 : size;
        for (unsigned i = 0; i < size; ++i) {
            m_color.data[i] = data[i];
        }
    }

};

} // namespace Material