#include "mesh_base.h"

#include "../Renderer/ShaderProgram.h"

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Renderer/TextureGL.h"
#include "../process/global.h"
#include "../manager/ResourceManager.h"

// TODO remove this
#include "windows.h"
#include <fstream>

Model::Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<type_pTextures> const& textures) :
	m_vertices(vertices),
	m_indices(indices),
	m_textures(textures)
{
	setupMesh();
}

void Model::Mesh::Draw(Renderer::ShaderProgram const & shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i]->activateTexture(i, shader);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Model::Mesh::setupMesh()
{
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texture_coord));

        glBindVertexArray(0);
}

void Model::Model::loadModel(std::filesystem::path const& path)
{
    Assimp::Importer import;
    aiScene const * scene = import.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }


    m_directory_path = path;
    m_directory_path.remove_filename();

    processNode(scene->mRootNode, scene);
}

void Model::Model::processNode(aiNode* node, aiScene const* scene)
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

Model::Mesh Model::Model::processMesh(aiMesh* mesh, aiScene const* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<type_pTextures> textures;

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
        std::vector<type_pTextures> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<type_pTextures> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh{ vertices, indices, textures };
}

std::vector<Model::type_pTextures> Model::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<type_pTextures> textures;
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

Model::Model::Model(std::filesystem::path const& path)
{
    loadModel(path);
}

void Model::Model::Draw(Renderer::ShaderProgram const & shader)
{
    for (auto&& mesh : m_meshes)
        mesh.Draw(shader);
}