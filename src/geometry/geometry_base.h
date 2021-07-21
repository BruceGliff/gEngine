#pragma once

#include <glm/vec3.hpp>
#include <ostream>

namespace NSGeometry {
    // TODO complete this
    class Transformation final {
    public:
        glm::vec3 displace{0.f};
        glm::vec3 rotate{0.f};
        glm::vec3 scale{1.f};

    public:
        Transformation() = default;
        Transformation(glm::vec3 const & disp, glm::vec3 const & rot, glm::vec3 const & scl);
        Transformation(Transformation const & tr);
        Transformation(Transformation && tr) noexcept;
        Transformation & operator= (Transformation const & tr);
        Transformation & operator= (Transformation && tr) noexcept;
        
        // Scale by default does not add up, but multiplies
        Transformation & operator+= (Transformation const & tr);
    };
} // namespace NSGeometry

// Scale by default does not add up, but multiplies
NSGeometry::Transformation operator+ (NSGeometry::Transformation const & lval, NSGeometry::Transformation const & rval);

glm::vec3 operator*(glm::vec3 const& vec, float x);
std::ostream& operator<<(std::ostream& os, glm::vec3 const& vec);