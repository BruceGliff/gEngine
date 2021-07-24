#pragma once

#include <memory>
#include <string>
#include "Model3D.h"

namespace NSModel {

// Primitive is a wrapper of Model3D with default loading path
class Primitive
    : public IModel {
public:
    // Path is hardcoded: /res/models/primitives/
    static std::string getFolderPath();
    virtual void Draw() const override;
    virtual ~Primitive();
};


// All classes declared in primitivesDEF.h
#define PRIMITIVE_DEF
#include "primitivesDEF.h"
#undef PRIMITIVE_DEF

} // namespace NSModel

