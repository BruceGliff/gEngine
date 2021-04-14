#pragma once

#include <filesystem>

#include "component_base.h"
#include "properties/properties.h"

#include <glm/vec3.hpp>


namespace Model {
    class IModel;
    class Primitive;
}
namespace Geometry  {
    class Transformation;
}

namespace Component
{
    class StaticMesh final : 
                            public component_base, 
                            public Property::IDrawable,
                            public Property::IMoveable,
                            public Property::IScalable
    {
        // Non owning ptr
        Model::IModel * model;
        

    public:
        // Load model from disk by path. It occures in ResourceManager.
        // If model with name already in ResourceManager, when get it from manager.
        StaticMesh(std::string const & name, std::filesystem::path const& relevantPath); // TODO check if it is needed

        // Takes model from ResourceManager. If it is not found, when where will be nullptr
        StaticMesh(std::string const& name);

        // Attach already loaded model in static mesh
        StaticMesh(Model::IModel * model);

        // Attach primitive.
        // TODO check if it is needed
        //StaticMesh(Model::Primitive const & primitive);

        StaticMesh()                                = delete;
        StaticMesh(StaticMesh const & )             = delete;
        StaticMesh(StaticMesh&&)                    = delete;
        StaticMesh & operator=(StaticMesh const &)  = delete;
        StaticMesh & operator=(StaticMesh &&)       = delete;


        void Draw(Geometry::Transformation const & tr) override;

        ~StaticMesh();
    };
}