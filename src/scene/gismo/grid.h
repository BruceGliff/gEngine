#pragma once

#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "../../properties/properties.h"
#include "../../actor/components/component_base.h"

namespace NSGeometry {
    class Transformation;
} //namespace NSGeometry

namespace NSScene {

class Grid final
    : public NSProperty::IDrawable      // Draw lines
    , public NSProperty::ICompound {    // Attach gismo (that has to be component)

    NSComponent::component_base * Gismo;

    int slices;
    float sizeOfSlice;
    unsigned int lenght;
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

    void Process(NSGeometry::Transformation const&) override; // To process gismo
    void Draw(NSGeometry::Transformation const &) override;   // To draw grid
};

} // namespace NSScene