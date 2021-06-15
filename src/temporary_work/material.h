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

#include <assimp/material.h>

#include <unordered_map>

namespace Material {

class Texture;
enum class MaterialType {
    Diffuse,
    Ambient,
    Specular
};

struct IMaterialNode final {
    Texture * m_pTexture {};
    Color m_color {};
    bool isTexture = false;

    IMaterialNode(Texture * pTexture)
        : m_pTexture{pTexture}
        , isTexture{true} 
    {}
    IMaterialNode(Color const & color)
        : m_color {color}
    {}

};


class Material final {
    // Type is IDiffuse, ISpecular, IAmbient
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
    void Set(IMaterialNode const & mElt, MaterialType mTy = MaterialType::Diffuse) {
        m_material.emplace(mTy, mElt);
    }

    void Set(Color const & color, MaterialType mTy = MaterialType::Diffuse) {
        m_material.emplace(mTy, color);
    }

    void Set(Texture * pTexture, MaterialType mTy = MaterialType::Diffuse) {
        m_material.emplace(mTy, pTexture);
    }


};

} // namespace Material