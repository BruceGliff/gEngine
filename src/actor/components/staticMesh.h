#pragma once

#include "component_base.h"
#include "properties/properties.h"

#include <filesystem>

#include <glm/vec3.hpp>

namespace Model {
    class IModel;
} // namespace Model
namespace Geometry  {
    class Transformation;
} // namespace Geometry
namespace Material {
    class Material;
} // namespace Material

namespace Component {

class StaticMesh final
    : public component_base
    , public Property::IDrawable
    , public Property::IMoveable
    , public Property::IScalable {
    // Non owning ptr
    Model::IModel * m_Model {};
    Material::Material * m_Material {};


public:
    // Takes model from ResourceManager. If it is not found, when where will be nullptr
    StaticMesh(std::string const& name);

    // Attachs already loaded model to static mesh
    StaticMesh(Model::IModel * model);

    StaticMesh()                                = delete;
    StaticMesh(StaticMesh const & )             = delete;
    StaticMesh(StaticMesh&&)                    = delete;
    StaticMesh & operator=(StaticMesh const &)  = delete;
    StaticMesh & operator=(StaticMesh &&)       = delete;

    // Attaches already created material to static mesh
    Material::Material * AttachMaterial(Material::Material *) noexcept;
    void Draw(Geometry::Transformation const & tr) override;

    ~StaticMesh();
};

} // namespace Component