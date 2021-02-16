#pragma once

#include <glm/vec3.hpp>

namespace Geometry
{

    // TODO complete this
    struct Transformation final
    {
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
        
        Transformation & operator+= (Transformation const & tr);
    };

    Transformation operator+ (Transformation const & lval, Transformation const & rval);
}