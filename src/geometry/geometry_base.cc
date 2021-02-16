#include "geometry_base.h"
using namespace Geometry;


Transformation(glm::vec3 const & disp, glm::vec3 const & rot, glm::vec3 const & scl) :
    displace{disp},
    rotate{rot},
    scale{scl}
{}
Transformation(Transformation const & tr) :
    displace{tr.displace},
    rotate{tr.rotate},
    scale{tr.scale}
{}
Transformation(Transformation && tr)
{
    *this = std::move(tr);
}
Transformation & operator= (Transformation const & tr)
{
    displace = tr.displace;
    rotate = tr.rotate;
    scale = tr.scale;
}
Transformation & operator= (Transformation && tr)
{
    displace = std::move(tr.displace);
    rotate = std::move(tr.rotate);
    scale = std::move(tr.scale);
}

Transformation & operator+= (Transformation const & tr)
{
    displace += tr.displace;
    rotate += tr.rotate;
    scale += tr.scale;
}


Transformation operator+ (Transformation const & lval, Transformation const & rval)
{
    Transformation tmp{lval};
    return tmp+=rval;
}