#pragma once
#include "mesh_base.h"

#include "../properties/properties.h"

#include <filesystem>
#include <unordered_map>


namespace Assimp {
    class Importer;
} // namespace Assimp
class aiScene;
class aiNode;
class aiMesh;
namespace Renderer {
    class TextureGL;
} // namspace Renderer;


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