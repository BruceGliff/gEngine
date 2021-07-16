#pragma once
#include "../debug/debug.h"


#include "color.h"

#include <variant>
#include <unordered_map>

namespace Material {

// FD of Texture class
class Texture;

// From here get Ambient, Diffuse, Specular as types
#define COLOR_COMPONENT_INCLUDE
#include "ColorComponent.h"
#undef COLOR_COMPONENT_INCLUDE


// Return ptr to component type.
// Diffuse*, Ambient*, Specular*.
// Or nullptr in case if type is not defined in ColorComponent.cc
template <typename T>
T * getComponentTy() {
  gWARNING("Type not defined" + typeid(T).name());
  return nullptr;
}

// Class represents type of MaterialComponent stored in node.
// It is Color or Texture*
class IMaterialNode final {
    std::variant<Color, Texture *> m_Component {};
public:
    IMaterialNode(Texture * texture) : m_Component{texture} {}
    IMaterialNode(Color const & color) : m_Component{color} {}
    IMaterialNode()                       = delete;
    IMaterialNode(IMaterialNode const &)  = delete;
    IMaterialNode(IMaterialNode && other) : m_Component{std::move(other.m_Component)} noexcept {}
    IMaterialNode & operator=(IMaterialNode const &)  = delete;
    IMaterialNode & operator=(IMaterialNode && other) noexcept {
      std::swap(m_Component, other.m_Component);
      return *this;
    }

    // Returns pointer to handled data (Color or Texture)
    // Returns nullptr if there is type missmatching
    template <typename T>
    T * get() noexcept {
        if constexpr (std::is_same<Color, T>::value)
            return std::get_if<Color>(&m_Component);
        if constexpr(std::is_same<Texture, T>::value) {
            Texture ** ppTexture = std::get_if<Texture*>(&m_Component);
            return ppTexture ? *ppTexture : nullptr;
        }
        gWARNING("Getting non Color and non Texture: " + typeid(T).name());
        return nullptr;
    }
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
    Texture * Set(Texture * texture) {
        auto [it, isOk] = m_Material.insert_or_assign(getComponentTy<NodeTy>(), texture);
        if (!isOk) {
          gWARNING("Insertion node to material fails!");
          return nullptr;
        }
        return it->second.template get<Texture>();
    }
    // Sets Component in material
    // fe: m.Set<Ambient>(Color)
    // Returns inserted Color* 
    template <typename NodeTy>
    Color * Set(Color const & color) {
        auto [it, isOk] = m_Material.insert_or_assign(getComponentTy<NodeTy>(), color);
        if (!isOk) {
          gWARNING("Insertion node to material fails!");
          return nullptr;
        }
        return it->second.template get<Color>();
    }
    // Gets IMaterialNode of Component's type (fe: Diffuse)
    template <typename NodeTy>
    IMaterialNode & Get() {
        MaterialMap::iterator it = m_Material.find(getComponentTy<NodeTy>());
        if (it == m_Material.end())
          gERROR("No such Component's type in material: " + typeid(NodeTy).name());
        return it->second;
    }

    // To future behavior. Processing all material nodes
    void process() {
        for (auto && n : m_Material)
            n.first->process();
    }
};


} // namespace Material