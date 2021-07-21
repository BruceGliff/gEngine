#include "model3D.h"

#include "debug/debug.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "process/global.h"
#include "manager/ResourceManager.h"

using namespace NSModel;

static Mesh processMesh(aiMesh* mesh, aiScene const* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned i = 0, numVerticies = mesh->mNumVertices; i != numVerticies; ++i)
        vertices.emplace_back(Vertex{
                                glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z}, // pos
                                glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z}, // norm
                                glm::vec2{mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].x : 0.f,
                                          mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].y : 0.f }  // text    
        });
    // process indices
    for (unsigned i = 0, numFaces = mesh->mNumFaces; i != numFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        // TODO make it like range inserter
        for (unsigned j = 0, numIndices = face.mNumIndices; j != numIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    return Mesh{ std::move(vertices), std::move(indices)};
}

void Model3D::processNode(aiNode* node, aiScene const* scene) {
    // TODO make throught range
    // process all the node's meshes (if any)
    for (unsigned i = 0, numMeshes = node->mNumMeshes; i != numMeshes ; ++i)
        m_Meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));

    // then do the same for each of its children
    for (unsigned i = 0, numChildren = node->mNumChildren; i != numChildren; ++i)
        processNode(node->mChildren[i], scene);
}

Model3D::Model3D(std::filesystem::path const& path) {
    Assimp::Importer import;
    aiScene const * scene = import.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        gWARNING(std::string{ "ASSIMP problem: cannot load model > " } + import.GetErrorString());
        return;
    }
    processNode(scene->mRootNode, scene);
}

void Model3D::Draw() const {
    for (auto&& mesh : m_Meshes)
        mesh.Draw();
}

Model3D::~Model3D() {}