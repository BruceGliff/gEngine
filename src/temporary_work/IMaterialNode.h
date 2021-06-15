/*

IMaterialNode is base for all materials component:
    Texture
    Color

//*/

namespace Material {

// Just classes
class IDiffuse {
public:
    virtual ~IDiffuse() {}
};

class IAmbient {
public:
    virtual ~IAmbient() {}
};

class ISpecular {
public:
    virtual ~ISpecular() {}
};


} // namespace Material