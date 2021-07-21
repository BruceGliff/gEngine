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

class Model3D
    : public IModel {
    std::vector<Mesh> m_Meshes;
    
    void processNode(aiNode* node, aiScene const * scene);
public:
    Model3D()                            = delete;
    Model3D(Model3D const &)             = delete;
    Model3D(Model3D &&)                  = delete;
    Model3D & operator=(Model3D const &) = delete;
    Model3D & operator=(Model3D &&)      = delete;


    Model3D(std::filesystem::path const& path);
    void Draw() const override;

    virtual ~Model3D();
};

} // namespace NSModel