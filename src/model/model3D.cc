#include "model3D.h"

#include "debug/debug.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "process/global.h"
#include "manager/ResourceManager.h"

void Model::Model3D::loadModel(std::filesystem::path const& path)
{
    Assimp::Importer import;
    aiScene const * scene = import.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        gWARNING(std::string{ "ASSIMP problem: cannot load model > " } + import.GetErrorString());
        return;
    }


    m_directory_path = path;
    m_directory_path.remove_filename();

    processNode(scene->mRootNode, scene);
}

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
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texture_coord = vec;
        }
        else
            vertex.texture_coord = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
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

    return Mesh{ vertices, indices, textures };
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
{
    loadModel(path);
}

void Model::Model3D::Draw(Renderer::ShaderProgram const & shader) const
{
    for (auto&& mesh : m_meshes)
        mesh.Draw(shader);
}