#pragma once

#include <cstring>
#include <iostream>

namespace Material {

class Color {
public:
    // 4 colors: red, green, blue, alpha
    // and data[4] aggregated
    
    union {
        struct {
            float r,g,b,a;
        };
        float data[4] {};
    } m_color;

    Color() {std::cout <<  " default color constructor\n";}

    // Construct Color by given components
    Color(float r, float g, float b, float a = 1.f) {
        std::cout <<  " component color constructor\n";
        m_color.r = r;
        m_color.g = g;
        m_color.b = b;
        m_color.a = a;
    }
    // Construct Color by given array
    // It is essential to use data with at least 16byte width
    Color(float const * data) {
        std::cout <<  " array color constructor\n";
        std::memcpy(m_color.data, data, sizeof(m_color));
    }
    // Construct Color by given array
    // lenght of data array can be less 4 floats
    Color(float const * data, unsigned size) {
        
        std::cout <<  " sized array color constructor\n";
        size = size > 4 ? 4 : size;
        for (unsigned i = 0; i < size; ++i) {
            m_color.data[i] = data[i];
        }
    }

    Color (Color const & other) {
        
        std::cout <<  " other color constructor\n";
        std::memcpy(m_color.data, other.m_color.data, sizeof(m_color));
    }

};

} // namespace Material