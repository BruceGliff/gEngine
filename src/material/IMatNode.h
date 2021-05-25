// Class represent interface of material node in Material class
// Color or texture is a node for Material class
// class Material {
//    IMatNode * diffuse; // can be Texture or color
//    IMatNode * specular; 
//    ...
// }

#pragma once

namespace Material {

class IMatNode {
public:
    virtual ~IMatNode() {}
};


} // namspace Material

