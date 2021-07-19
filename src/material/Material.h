#pragma once
#include "../debug/debug.h"


#include "color.h"

#include <variant>
#include <unordered_map>
#include <string>

namespace Renderer {
    class ShaderProgram;
} // namespace Renderer

namespace MaterialNS {

// FD of Texture class
class Texture;

// From here get Ambient, Diffuse, Specular as types
#define COLOR_COMPONENT_INCLUDE
#include "ColorComponent.h"
#undef COLOR_COMPONENT_INCLUDE


// Return ptr to component type.
// Diffuse*, Ambient*, Specular*.
template <typename T>
T * getComponentTy();

// Class represents type of MaterialComponent stored in node.
// It is Color or Texture*
class IMaterialNode final {
    std::variant<Color, Texture *> m_Component {};
public:
    IMaterialNode(Texture * texture);
    IMaterialNode(Color const & color);
    IMaterialNode()                       = delete;
    IMaterialNode(IMaterialNode const &)  = delete;
    IMaterialNode(IMaterialNode && other) noexcept;
    IMaterialNode & operator=(IMaterialNode const &)  = delete;
    IMaterialNode & operator=(IMaterialNode && other) noexcept;

    void activate(std::string const & prefix, unsigned offset, Renderer::ShaderProgram const & shader) const;

    // Returns pointer to handled data (Color or Texture)
    // Returns nullptr if there is type missmatching
    template <typename T>
    T * get() noexcept;
};

class Material final {
    // map of Diffuse and Color/Texture
    typedef std::unordered_map<IMaterialComponentTy *, IMaterialNode> MaterialMap;
    MaterialMap m_Material;

public:
    // Sets Component in material
    // fe: m.Set<Diffuse>(Texture)
    // Returns inserted Texture* 
    template <class NodeTy>
    Texture * Set(Texture * texture);
    // Sets Component in material
    // fe: m.Set<Ambient>(Color)
    // Returns inserted Color* 
    template <typename NodeTy>
    Color * Set(Color const & color);
    // Gets IMaterialNode of Component's type (fe: Diffuse)
    template <typename NodeTy>
    IMaterialNode & Get();

    // To future behavior. Processing all material nodes
    void process(Renderer::ShaderProgram const & shader) const;
};

#include "material.hpp"

} // namespace Material