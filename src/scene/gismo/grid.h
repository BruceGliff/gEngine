#pragma once

#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glad/glad.h>

#include "../../properties/properties.h"
#include "../../actor/components/component_base.h"

namespace Geometry { class Transformation; }

namespace Scene
{

    class Grid final :  public Property::IDrawable, // Draw lines
                        public Property::ICompound  // Attach gismo (that has to be component) 
    {
        Component::component_base * Gismo;

        int slices;
        float sizeOfSlice;
        GLuint lenght;
        unsigned int VAO, VBO, EBO;
        std::vector<glm::vec3> vertices;
        std::vector<glm::uvec2> indices;

        void GenerateGrid(); 
    public:
        Grid();
        Grid(Grid const &&)             = delete;
        Grid(Grid &&)                   = delete;
        Grid & operator=(Grid const &&) = delete;
        Grid & operator=(Grid &&)       = delete;

        void Process(Geometry::Transformation const&) override; // To process gismo
        void Draw(Geometry::Transformation const &) override;   // To draw grid
    };

} // namespace Scene