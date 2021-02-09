#pragma once

#include "component_base.h"
#include "../../properties/properties.h"

#include <glm/vec3.hpp>


namespace Model
{
    class Model;
}

namespace Component
{
    class StaticMesh final : public component_base, public Property::IDrawable, public Property::IMoveable
    {
        Model::Model * model = nullptr;
        

    public:
        StaticMesh(std::filesystem::path const& path);

        StaticMesh()                                = delete;
        StaticMesh(StaticMesh const & )             = delete;
        StaticMesh(StaticMesh&&)                    = delete;
        StaticMesh & operator=(StaticMesh const &)  = delete;
        StaticMesh & operator=(StaticMesh &&)       = delete;


        void Draw(Renderer::ShaderProgram const & ) override;

        ~StaticMesh();
    };
}