#include "model3D.h"

#include "debug/debug.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "process/global.h"
#include "manager/ResourceManager.h"

void Model::Model3D::processNode(aiNode* node, aiScene const* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Model::Mesh Model::Model3D::processMesh(aiMesh* mesh, aiScene const* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Renderer::TextureGL*> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.emplace_back(Vertex{
                                glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z}, // pos
                                glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z}, // norm
                                glm::vec2{mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].x : 0.f,
                                          mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i].y : 0.f }  // text    
        });
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // TODO optimize this
        std::vector<Renderer::TextureGL*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Renderer::TextureGL*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh{ std::move(vertices), std::move(indices), std::move(textures) };
}

std::vector<Renderer::TextureGL*> Model::Model3D::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<Renderer::TextureGL*> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        Renderer::ETextureType texType;
        switch (type)
        {
        case aiTextureType_DIFFUSE:
            texType = Renderer::ETextureType::DIFFUSE;
            break;
        case aiTextureType_SPECULAR:
            texType = Renderer::ETextureType::SPECULAR;
            break;
        default:
            texType = Renderer::ETextureType::DIFFUSE;
            break;
        }

        textures.push_back(GLOBAL::GetResManager().loadTexture(m_directory_path / std::filesystem::path{ str.C_Str() }, texType));

    }
    return textures;
}

Model::Model3D::Model3D(std::filesystem::path const& path)
    : m_importer{new Assimp::Importer{}}
    , m_directory_path{path}
{
    m_directory_path = path;
    m_directory_path.remove_filename();
    m_model_name = path.filename().string();
    
    m_scene = m_importer->ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) {
        gWARNING(std::string{ "ASSIMP problem: cannot load model > " } + m_importer->GetErrorString());
        return;
    }

    retrieveAllMeshInfo()
}

void Model::Model3D::Draw(Geometry::Transformation const & transform) {
    drawNode(m_scene->mRootNode, transform);
}

void Model::Model3D::drawNode(aiNode * node, Geometry::Transformation const & transform) {
    // process all the node's meshes (if any)
    for (unsigned i = 0, numMeshes = node->mNumMeshes; i != numMeshes; ++i) {
        aiMesh* mesh = m_scene->mMeshes[node->mMeshes[i]];
        drawMesh(mesh, transform); // TODO think how to change transformation
    }
    // then do the same for each of its children
    for (unsigned i = 0, numChildren = node->mNumChildren; i != numChildren; ++i) {
        drawNode(node->mChildren[i], transform); // TODO think how to change transformation
    }
}
void Model::Model3D::drawMesh(aiMesh * mesh, Geometry::Transformation const & transform) {


}

void Model::Model3D::processMesh(aiMesh * mesh) {
    collectBuffersInfo(mesh);
    if ()

}

void Model::Model3D::collectTexturesInfo() {

}

void Model::Model3D::collectBuffersInfo(aiMesh * mesh) {

}

void Model::Model3D::retrieveAllMeshInfo(aiNode * node) {
    for (unsigned i = 0, numMeshes = node->mNumMeshes; i != numMeshes; ++i) {
        aiMesh* mesh = m_scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh);
    }
    for (unsigned i = 0, numChildren = node->mNumChildren; i != numChildren; ++i) {
        retrieveAllMeshInfo(node->mChildren[i]);
    }
}
