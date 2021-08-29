#pragma once

#include "component_base.h"
#include "../../properties/properties.h"

#include <filesystem>

#include <glm/vec3.hpp>

namespace NSModel {
    class IModel;
} // namespace NSModel
namespace NSGeometry  {
    class Transformation;
} // namespace NSGeometry
namespace NSMaterial {
    class Material;
} // namespace NSMaterial

namespace NSComponent {

class StaticMesh final
    : public component_base
    , public NSProperty::IDrawable
    , public NSProperty::IMoveable
    , public NSProperty::IScalable {
    // Non owning ptrs
    NSModel::IModel * m_Model {};
    NSMaterial::Material * m_Material {};


public:
    // Takes model from ResourceManager. If it is not found, when where will be nullptr
    StaticMesh(std::string const& name);

    // Attachs already loaded model to static mesh
    StaticMesh(NSModel::IModel * model);

    StaticMesh()                                = delete;
    StaticMesh(StaticMesh const & )             = delete;
    StaticMesh(StaticMesh&&)                    = delete;
    StaticMesh & operator=(StaticMesh const &)  = delete;
    StaticMesh & operator=(StaticMesh &&)       = delete;

    // Attaches already created material to static mesh
    NSMaterial::Material * AttachMaterial(NSMaterial::Material *) noexcept;
    void Draw(NSGeometry::Transformation const & tr) override;

    ~StaticMesh();
};

} // namespace NSComponent