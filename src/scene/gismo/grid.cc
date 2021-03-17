#include "grid.h"

#include "../../renderer/ShaderProgram.h"
#include "../../process/global.h"
#include "../../manager/ResourceManager.h"
#include "../../actor/actor.h"
#include "../../actor/components/camera.h"
#include "../../geometry/geometry_base.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace Scene;

Grid::Grid() :
    slices{10},
    lenght{static_cast<GLuint>(slices * slices * 8)},
    sizeOfSlice{2.f}
{
    GenerateGrid();
    
    shader = GLOBAL::GetResManager().loadShaders("gridShader", "res/shaders/grid/grid.vs", "res/shaders/grid/grid.fs");
}

void Grid::GenerateGrid()
{
    for (int i = -slices / 2 + 1, j = 0; i != slices / 2; ++i, j += 4)
    {
        float const x1 = sizeOfSlice * i;
        float const z1 = sizeOfSlice * (-slices / 2);
        float const z2 = -z1;
        
        // First line perpend oX
        vertices.push_back(glm::vec3(x1, 0.f, z1));
        vertices.push_back(glm::vec3(x1, 0.f, z2));
        indices.push_back(glm::uvec2(j, j + 1));

        // Second line perpend oZ
        vertices.push_back(glm::vec3(z1, 0.f, x1));
        vertices.push_back(glm::vec3(z2, 0.f, x1));
        indices.push_back(glm::uvec2(j + 2, j + 3));
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(glm::uvec2), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Grid::Draw(Geometry::Transformation const & tr)
{
    shader->Use();
    auto mainCam = GLOBAL::GetPlayer().GetComponentByName<Component::camera>("camera");
    shader->setMat4("view", mainCam->GetViewMatrix());
    shader->setMat4("projection", mainCam->GetProjectionMatrix());
    glm::mat4 const model_tr_matrix = glm::translate(glm::mat4{1.0f}, tr.displace);
    glm::mat4 const model_matrix = glm::scale(model_tr_matrix, tr.scale);
    shader->setMat4("model", model_matrix);

    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, lenght, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void Grid::Process(Geometry::Transformation const & tr)
{
    Draw(tr);
    //reinterpret_cast<Property::IDrawable *>(Gismo)->Draw(tr);
}