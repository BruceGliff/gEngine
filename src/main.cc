#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cmath>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureGL.h"

// This is should be at resource manager
#include "Resources/window/window_base.h"


GLfloat verteces[] =
{
    // position           // color          // texture
    -0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,    0.f, 0.f, // G
     0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f,    1.f, 0.f, // R
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f, // G
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f, // G
    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f, // B
    -0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,

    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
     0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,
     0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,
    -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,

    -0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
    -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,
    -0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,

     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,
     0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
     0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
     0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,

    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
     0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,

    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,
    -0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,
    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f
};
unsigned int indices[] =
{
    0, 2, 3,
    0, 1, 2
};

// VS
char const* vertex_shader_PATH = "res/shaders/vertex.glsl";
// FS
char const* fragment_shader_PATH = "res/shaders/fragment.glsl";


int main(int argc, char * argv[])
{        
    Resources::glWindows win{};

    /* Initialize glad */
    if (!gladLoadGL())
    {
        std::cerr << "Cannot initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL ver: " << glGetString(GL_VERSION) << std::endl;

    // Fill bachground with color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    {// ResourceManager has shaders constext inside. so it has to be terminated before glfw
        Resources::ResourcesManager resMng{ argv[0] };
        auto pShaderProgram = resMng.loadShaders("DefaultSahder", vertex_shader_PATH, fragment_shader_PATH);
        if (!pShaderProgram->IsCompiled())
        {
            std::cerr << "ERROR:: Creating Shader program in main\n" << std::endl;
            glfwTerminate();
            return -1;
        }

        auto texture = resMng.loadTexture("DefaultTexture", "res/textures/weed_pepe.jpg");

// BUFFER IMP
// ***********************************************************************************
        // Vertex array object .. all together: vertices and indices
        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);
        // Vertex buffer object .. vertices
        unsigned int VBO = 0;
        glGenBuffers(1, &VBO);
        // Element buffer object .. indices
        unsigned int EBO = 0;
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // copy our vertices array in a vertex buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), verteces, GL_STATIC_DRAW);
        // copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
// ***********************************************************************************


// MATRIX MATHEMATIC
// ***********************************************************************************
        // Transformation
        // model matrix has all transformations (traslations, scaling, rotation) at the world space
        glm::mat4 model = glm::rotate(glm::mat4{ 1.f }, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));

        // it is camera
        // note that we're translating the scene in the reverse direction of where we want to move
        glm::vec3 cameraPosition{ 0.f, 0.f, 3.f };
        glm::vec3 cameraTarget{ 0.f, 0.f, 0.f };
        // glm::vec3 cameraDir{ cameraTarget - cameraPosition }; This will be calculated in LookAt
        

        // to the viewport
        glm::mat4 projection{ glm::perspective(glm::radians(45.0f), 400.0f / 400.0f, 0.1f, 100.0f) };

       
// ***********************************************************************************


        // To activate shader program
        pShaderProgram->Use();
        pShaderProgram->SetID("tex", 0);

        // belive what projection and view does not change
        pShaderProgram->loadMatrix("projection", projection);


        // Now we are ready for drawing
        /* Loop until the user closes the window */
        glEnable(GL_DEPTH_TEST);

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        while (!win)
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Drawing
            pShaderProgram->Use();
            // Now we connect vao to draw. it is already current, but it can be different for different obejcts in future
            glBindVertexArray(VAO);
            // Make texture to draw active
            texture->bind();

            //Change camera position
            float const radius = 10.f;
            float const xCam = std::sin(glfwGetTime()) * radius;
            float const zCam = std::cos(glfwGetTime()) * radius;
            glm::mat4 const view{ glm::lookAt(glm::vec3{xCam, 0.f, zCam}, cameraTarget, glm::vec3{0.f, 1.f, 0.f}) };
            pShaderProgram->loadMatrix("view", view);

            // Draw current VAO
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[0]);
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3{ 0.f, 1.f, 0.f });
                pShaderProgram->loadMatrix("model", model);
            }
            glDrawArrays(GL_TRIANGLES, 0, 36);
            for (unsigned int i = 1; i < 10; ++i)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle) * (float)glfwGetTime(), glm::vec3(1.0f * i, 0.3f * (10-i), 5.f));
                pShaderProgram->loadMatrix("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            win.Draw();
        }
    } // ResourceManager is terminated

    return 0;
}
