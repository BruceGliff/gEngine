#include "mesh_base.h"

#include "../renderer/ShaderProgram.h"

#include <glad/glad.h>
#include "renderer/TextureGL.h"

Model::Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<Renderer::TextureGL*> const& textures) :
    m_vertices(vertices),
    m_indices(indices),
    m_textures(textures)
{
    setupMesh();
}
Model::Mesh::Mesh(std::vector<Vertex> && vertices, std::vector<unsigned int> && indices, std::vector<Renderer::TextureGL*> && textures) :
    m_vertices(std::move(vertices)),
    m_indices(std::move(indices)),
    m_textures(std::move(textures))
{
    setupMesh();
}

void Model::Mesh::Draw(Renderer::ShaderProgram const & shader) const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i != m_textures.size(); i++)
    {
        m_textures[i]->activateTexture(i, shader);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    // Just to avoid warnings
    GLsizei const size = static_cast<GLsizei>(m_indices.size());
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
}