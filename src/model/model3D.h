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
                        : public IModel
                        , public Property::IDrawable
                        {
        aiScene const * m_scene {};

        std::filesystem::path m_directory_path;
        std::string m_model_name;

        void drawMesh(aiMesh * mesh, Geometry::Transformation const & transform);
        void drawNode(aiNode * node, Geometry::Transformation const & transform);

        struct GPUBuffTy { // unique for each mesh!
            unsigned VAO {};
            unsigned VBO {};
            unsigned EBO {}; 
        };
        using BuffInfoTy = std::unordered_map<unsigned, GPUBuffTy>; // unsigned = mesh idx
        using TextureInfoTy = std::unordered_map<unsigned, std::vector<Renderer::TextureGL *>>; // unsigned = mat idx
        
        // for mesh calls collectBuffersInfo and collectTexturesInfo
        void processMesh(aiMesh * mesh);
        // loads TextureGL and fill unordered_map
        void collectTexturesInfo();
        // generates all buffers and fill unordered_map
        void collectBuffersInfo(aiMesh * mesh);
        // goes down to mesh and processed it
        void retrieveAllMeshInfo(aiNode * node);

    public:
        Model3D(std::filesystem::path const& path);
        void Draw(Geometry::Transformation const & transform) override;

        ~Model3D();

    };
} // namespace Model