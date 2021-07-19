#pragma once
#include "mesh_base.h"

#include "../properties/properties.h"

#include <filesystem>
#include <unordered_map>


namespace Assimp {
    class Importer;
} // namespace Assimp
struct aiScene;
struct aiNode;

namespace Model { 

class Model3D final
    : public IModel {
    std::vector<Mesh> m_Meshes;
    
    void processNode(aiNode* node, aiScene const * scene);

public:
    Model3D(std::filesystem::path const& path);
    void Draw(Renderer::ShaderProgram const & shader) const override;

};

} // namespace Model