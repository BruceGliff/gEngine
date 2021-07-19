#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>

// TODO This is just from tutorial for testing
// Make it on my way

namespace NSModel {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coord;
};

class IModel {
protected:
    IModel() {}
public:
    virtual void Draw() const = 0;
    virtual ~IModel() {}
};

// TODO accumulate all meshes into one
class Mesh final
    : public IModel {
    unsigned VAO{}, VBO{}, EBO{};
    void setupMesh();

public:
    Mesh(std::vector<Vertex> const & vertices, std::vector<unsigned> const & indices);
    Mesh(std::vector<Vertex> && vertices, std::vector<unsigned> && indices);
    void Draw() const override;
    
public:
    std::vector<Vertex>   m_vertices;
    std::vector<unsigned> m_indices;
};

} // namespace NSModel