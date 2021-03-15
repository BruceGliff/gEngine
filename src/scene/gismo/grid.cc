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
    slices{50},
    lenght{static_cast<GLuint>(slices * slices * 8)},
    sizeOfSlice{2.f}
{
    GenerateGrid();
    
    shader = GLOBAL::GetResManager().loadShaders("gridShader", "res/shaders/grid/grid.vs", "res/shaders/grid/grid.fs");
}

void Grid::GenerateGrid()
{
    for(int j = 0; j <= slices; ++j) 
    {
        for(int i = 0; i <= slices; ++i) 
        {
            // float const x = (float)i/(float)slices;
            // float const y = 0;
            // float const z = (float)j/(float)slices;

            float const x = (i - slices / 2) * sizeOfSlice;
            float const y = 0;
            float const z = (j - slices / 2) * sizeOfSlice;

            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for(int j = 0; j < slices; ++j) 
    {
        for(int i = 0; i < slices; ++i) 
        {
            int row1 =  j    * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
        }
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(glm::uvec4), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

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