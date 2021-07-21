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

namespace NSModel { 

class Model3D final
    : public IModel {
    std::vector<Mesh> m_Meshes;
    
    void processNode(aiNode* node, aiScene const * scene);

public:
    Model3D(std::filesystem::path const& path);
    void Draw() const override;

};

} // namespace NSModel