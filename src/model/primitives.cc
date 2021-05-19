#include "primitives.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace Model;

static std::unique_ptr<Mesh> getMesh(std::vector<Renderer::TextureGL*> const &, std::string const &);

Primitive::Primitive(   std::vector<Renderer::TextureGL*> const & texturesIn,
                        std::string const & name) {
    mesh = getMesh(texturesIn, name);
}
void Primitive::Draw(Renderer::ShaderProgram const & shader) const {
    mesh->Draw(shader);
}

// Gets down at model tree and find first actual mesh
aiMesh * recursiveTreeCheck(aiNode * node, aiScene const * scene) {
    if (node->mNumMeshes) {
        return scene->mMeshes[node->mMeshes[0]];
    }
    for (unsigned int i = 0; i != node->mNumChildren; ++i) {
        aiMesh * mesh = recursiveTreeCheck(node->mChildren[i], scene);
        if (mesh)
            return mesh;
    }

    return nullptr;
}

std::unique_ptr<Mesh> getMesh(std::vector<Renderer::TextureGL*> const & textures, std::string const & name) {
    Assimp::Importer import;
    std::filesystem::path PathToModel = GLOBAL::GetResManager().getPathToExucutable() / "res/models/primitives" / (name + ".obj");
    aiScene const * scene = import.ReadFile(PathToModel.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        gWARNING(std::string{ "ASSIMP problem: cannot load model > " } + import.GetErrorString());
        return nullptr;
    }
    aiNode * node = scene->mRootNode;

    aiMesh * mesh = recursiveTreeCheck(node, scene);
    if (!mesh) {
        gWARNING(std::string{"No model in "} + PathToModel.string());
        return nullptr;
    }

    // Assume that there is only one node in scene and one object.
    // If scene is more complicated, then use standart Model3D

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    vertices.reserve(mesh->mNumVertices);

    for (unsigned int i = 0; i != mesh->mNumVertices; i++)
    {
        vertices.emplace_back(Vertex{
                                glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z}, // pos
                                glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z}, // norm
                                glm::vec2{mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].x : 0.f,
                                          mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].y : 0.f }  // text    
        });
    }
    // process indices
    // TODO find out how to reserve memory for it
    for (unsigned int i = 0; i != mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j != face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return std::make_unique<Mesh>(std::move(vertices), std::move(indices), std::move(textures));
}


