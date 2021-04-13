#include "primitives.h"
#include "../process/global.h"
#include "../manager/ResourceManager.h"

using namespace Model;

Plane::Plane() {
    Resources::ResourcesManager & Mgr = GLOBAL::GetResManager();
    
    mesh = std::make_unique<Mesh> (generateVertices(), generateIndices(), std::vector<Renderer::TextureGL*>{});
}
Plane::Plane(std::vector<Renderer::TextureGL*> const & textures) {
    mesh = std::make_unique<Mesh> (generateVertices(), generateIndices(), textures);
}

std::vector<Vertex> Plane::generateVertices() {
    return std::vector<Vertex>  {
                                    Vertex{glm::vec3{-0.5f, 0.5f, 0.f},  glm::vec3{0.f, 0.f, 1.f}, glm::vec2{0.f, 1.f}},
                                    Vertex{glm::vec3{0.5f, 0.5f, 0.f},   glm::vec3{0.f, 0.f, 1.f}, glm::vec2{1.f, 1.f}},
                                    Vertex{glm::vec3{-0.5f, -0.5f, 0.f}, glm::vec3{0.f, 0.f, 1.f}, glm::vec2{0.f, 0.f}},
                                    Vertex{glm::vec3{0.5f, -0.5f, 0.f},  glm::vec3{0.f, 0.f, 1.f}, glm::vec2{1.f, 0.f}}
                                };
}

std::vector<unsigned int> Plane::generateIndices() {
    return std::vector<unsigned int>    {
                                            0, 1, 2,
                                            2, 1, 3
                                        };
}

void Plane::Draw(Renderer::ShaderProgram const & shader) const {
    mesh->Draw(shader);
}
