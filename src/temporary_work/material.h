/*
class contains all information about material

//*/

/**
 * FE: creating backpack class
 * class backpack : public actor {
 *  backpack() {
 *      Model * model = resMgr.loadModel("backpack");
 *      StaticMesh * component = AttachComponent<StaticMesh>("backpack_mesh", model);
 *      Material * material = resMgr.loadMaterial("backpack_material");
 *      material->Set(Color{255,255,255}, MaterialType::Ambient);
 *      material->Set(resMgr.loadTexture("container"), MaterialType::Specular);
 *      component->AttachMaterial(material)
 *  }
 * };
*/


#include "color.h"

#include <unordered_map>
#include <iostream>

namespace Material {

class Texture;
enum class MaterialType : unsigned {
    Diffuse,
    Ambient,
    Specular
};

class IMaterialNode final {
    Texture * m_pTexture {};
    Color m_color {};
    //bool isTexture = false;

public:
    // getter of Color* or Texture*
    template <typename T>
    T * get() {
        if constexpr (std::is_same<Color, T>()) {
            // if Texture exist(that means no Color) -> return nullptr;
            if (m_pTexture) {
                return nullptr;
            }
            return &m_color;
        } else if constexpr (std::is_same<Texture, T>()) {
            // TODO check if texture
            return m_pTexture;
        }
    }

    IMaterialNode() {}

    IMaterialNode(Texture * pTexture)
        : m_pTexture{pTexture} {}
    IMaterialNode(Color const & color)
        : m_color {color} {}

    bool isTexture() {
        return m_pTexture;
    }

    IMaterialNode(IMaterialNode const & other)
        : m_pTexture{other.m_pTexture}
        , m_color{other.m_color} {}

    IMaterialNode(IMaterialNode && other)
        : m_pTexture{other.m_pTexture}
        , m_color{other.m_color} {}

    IMaterialNode & operator=(IMaterialNode const & other) {
        m_pTexture = other.m_pTexture;
        m_color = other.m_color;
        return *this;
    }
};


class Material final {
    // Type is Diffuse, Specular, Ambient
    std::unordered_map<MaterialType, IMaterialNode> m_material;
// first work with DSA
    // pIMaterialNode Diffuse             {};
    // pIMaterialNode Specular            {};
    // pIMaterialNode Ambient             {};
    /*
    pIMaterialNode Emissive            {};
    pIMaterialNode Heigh               {};
    pIMaterialNode Normals             {};
    pIMaterialNode Shininess           {};
    pIMaterialNode Opacity             {};
    pIMaterialNode Dispacement         {};
    pIMaterialNode LightMat            {};
    pIMaterialNode Reflection          {};
    pIMaterialNode Base_color          {};
    pIMaterialNode Normal_camera       {};
    pIMaterialNode Emission_colo       {};
    pIMaterialNode Metalness           {};
    pIMaterialNode Diffuse_roughness   {};
    pIMaterialNode Ambient_occlusion   {};
 //*/

public:
    // sets material element in material colaboration:
    // material.Set(ptr_to_texture, Diffuse)
    // material.Set(color, Ambient)
    // in case of texture ->    copy pointer
    // in case of color ->      copy color
    IMaterialNode & Set(IMaterialNode const & mElt, MaterialType mTy = MaterialType::Diffuse) {
        auto [it, isOk] = m_material.insert_or_assign(mTy, mElt);
        return it->second;
        // TODO assertion on return value
    }

    IMaterialNode & Set(Color const & color, MaterialType mTy = MaterialType::Diffuse) {
        auto [it, isOk] = m_material.insert_or_assign(mTy, color);
        return it->second;
    }

    IMaterialNode & Set(Texture * pTexture, MaterialType mTy = MaterialType::Diffuse) {
        auto [it, isOk] = m_material.insert_or_assign(mTy, pTexture);
        return it->second;
    }

    // IMaterialNode & operator[](MaterialType mTy) {
        
    // };


};

} // namespace Material