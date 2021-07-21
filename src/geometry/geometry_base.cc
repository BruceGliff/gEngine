#include "geometry_base.h"

using namespace NSGeometry;

Transformation::Transformation(glm::vec3 const & disp, glm::vec3 const & rot, glm::vec3 const & scl)
    : displace{disp}
    , rotate{rot}
    , scale{scl} {}

Transformation::Transformation(Transformation const & tr)
    : displace{tr.displace}
    , rotate{tr.rotate}
    , scale{tr.scale} {}

Transformation::Transformation(Transformation && tr) noexcept {
    *this = std::move(tr);
}

Transformation & Transformation::operator= (Transformation const & tr) {
    displace = tr.displace;
    rotate = tr.rotate;
    scale = tr.scale;
    return *this;
}

Transformation & Transformation::operator= (Transformation && tr) noexcept {
    displace = std::move(tr.displace);
    rotate = std::move(tr.rotate);
    scale = std::move(tr.scale);
    return *this;
}

Transformation & Transformation::operator+= (Transformation const & tr) {
    displace += tr.displace;
    rotate += tr.rotate;
    scale *= tr.scale;
    return *this;
}


Transformation operator+(Transformation const & lval, Transformation const & rval) {
    Transformation tmp{lval};
    return tmp+=rval;
}

glm::vec3 operator*(glm::vec3 const& vec, float x) {
    glm::vec3 tmp{ vec };
    tmp.x *= x;
    tmp.y *= x;
    tmp.z *= x;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, glm::vec3 const& vec) {
    os << "[X: " << vec.x << ", Y: " << vec.y << ", Z: " << vec.z << "]" << std::endl;
    return os;
}
