#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cmath>

#include "process/global.h"
#include "manager/ResourceManager.h"
#include "renderer/ShaderProgram.h"
#include "renderer/TextureGL.h"
#include "window/window_base.h"
#include "actor/actor.h"
#include "actor/components/camera.h"



GLfloat verteces[] =
{
    // position           // color          // texture   // Normals
    -0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.f, 1.f,    0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.f, 0.f,    0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    0.f, 0.f,    0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.f, 0.f, 1.f,    0.f, 1.f,    0.0f,  1.0f,  0.0f
};
unsigned int indices[] =
{
    0, 2, 3,
    0, 1, 2
};


std::string const SHADER_PATH{ "res/shaders/" };

int main(int argc, char * argv[])
{        
    GLOBAL::Initialize(argv[0], 1600, 900, "OOP Changes!");

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
        Resources::ResourcesManager& resMng = GLOBAL::GetResManager();
        auto pObjShaderProgram = resMng.loadShaders("objShader", SHADER_PATH + "Cube.vs", SHADER_PATH + "Cube.fs");
        if (!pObjShaderProgram->IsCompiled())
        {
            std::cerr << "ERROR:: Creating objShader program in main\n" << std::endl;
            glfwTerminate();
            return -1;
        }
        auto pLightShaderProgram = resMng.loadShaders("lightShader", SHADER_PATH + "lightCube.vs", SHADER_PATH + "lightCube.fs");
        if (!pLightShaderProgram->IsCompiled())
        {
            std::cerr << "ERROR:: Creating lightShader program in main\n" << std::endl;
            glfwTerminate();
            return -1;
        }

        auto textureDiffuse = resMng.loadTexture("BoxDiff", "res/textures/container.png");
        auto textureSpecular = resMng.loadTexture("BoxSpec", "res/textures/container_specular.png");

// BUFFER IMP MODEL
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Set normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Set texture pos
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

// ***********************************************************************************

// BUFFER IMP LIGHT
// ***********************************************************************************
        unsigned int lightVAO = 0;
        glGenVertexArrays(1, &lightVAO);

        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);



        // Now we are ready for drawing
        /* Loop until the user closes the window */
        glEnable(GL_DEPTH_TEST);

        glm::vec3 cubePositions[] = 
        {
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
        glm::vec3 pointLightPositions[] = 
        {
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  0.0f, -3.0f)
        };

        // Easiest benchmark
        int delta_frame = 0;
        auto const prev_time = glfwGetTime();

        Resources::glWindows& win = GLOBAL::GetWindow();

        pObjShaderProgram->Use();
        // Load texture
        pObjShaderProgram->SetInt("material.diffuse", 0);
        textureDiffuse->bind();
        pObjShaderProgram->SetInt("material.specular", 1);
        textureSpecular->bind();

        while (!win.ProcessInput())
        {
            ++delta_frame;

            /* Render here */
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /// Drawing cube!!
            // *********************************************
            pObjShaderProgram->Use(); 

            // Loading colors
            pObjShaderProgram->setFloat("material.shininess", 32.0f);
            // Light source is second cube!
            // directional light
            pObjShaderProgram->setVec3("dirLight.direction", glm::vec3{ -0.2f, -1.0f, -0.3f });
            pObjShaderProgram->setVec3("dirLight.ambient", glm::vec3{ 0.05f, 0.05f, 0.05f });
            pObjShaderProgram->setVec3("dirLight.diffuse", glm::vec3{ 0.4f, 0.4f, 0.4f });
            pObjShaderProgram->setVec3("dirLight.specular", glm::vec3{ 0.5f, 0.5f, 0.5f });
            // point light 1
            pObjShaderProgram->setVec3("pointLights[0].position", pointLightPositions[0]);
            pObjShaderProgram->setVec3("pointLights[0].ambient", glm::vec3{ 0.05f, 0.05f, 0.05f });
            pObjShaderProgram->setVec3("pointLights[0].diffuse", glm::vec3{ 0.f, 0.8f, 0.8f });
            pObjShaderProgram->setVec3("pointLights[0].specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
            pObjShaderProgram->setFloat("pointLights[0].constant", 1.0f);
            pObjShaderProgram->setFloat("pointLights[0].linear", 0.09);
            pObjShaderProgram->setFloat("pointLights[0].quadratic", 0.032);
            // point light 2
            pObjShaderProgram->setVec3("pointLights[1].position", pointLightPositions[1]);
            pObjShaderProgram->setVec3("pointLights[1].ambient", glm::vec3{ 0.05f, 0.05f, 0.05f });
            pObjShaderProgram->setVec3("pointLights[1].diffuse", glm::vec3{ 0.8f, 0.f, 0.8f });
            pObjShaderProgram->setVec3("pointLights[1].specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
            pObjShaderProgram->setFloat("pointLights[1].constant", 1.0f);
            pObjShaderProgram->setFloat("pointLights[1].linear", 0.09);
            pObjShaderProgram->setFloat("pointLights[1].quadratic", 0.032);
            // point light 3
            pObjShaderProgram->setVec3("pointLights[2].position", pointLightPositions[2]);
            pObjShaderProgram->setVec3("pointLights[2].ambient", glm::vec3{ 0.05f, 0.05f, 0.05f });
            pObjShaderProgram->setVec3("pointLights[2].diffuse", glm::vec3{ 0.8f, 0.8f, 0.f });
            pObjShaderProgram->setVec3("pointLights[2].specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
            pObjShaderProgram->setFloat("pointLights[2].constant", 1.0f);
            pObjShaderProgram->setFloat("pointLights[2].linear", 0.09);
            pObjShaderProgram->setFloat("pointLights[2].quadratic", 0.032);
            // point light 4
            pObjShaderProgram->setVec3("pointLights[3].position", pointLightPositions[3]);
            pObjShaderProgram->setVec3("pointLights[3].ambient", glm::vec3{ 0.05f, 0.05f, 0.05f });
            pObjShaderProgram->setVec3("pointLights[3].diffuse", glm::vec3{ 0.8f, 0.f, 0.f });
            pObjShaderProgram->setVec3("pointLights[3].specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
            pObjShaderProgram->setFloat("pointLights[3].constant", 1.0f);
            pObjShaderProgram->setFloat("pointLights[3].linear", 0.09);
            pObjShaderProgram->setFloat("pointLights[3].quadratic", 0.032);


            //Change camera position
            // TODO think about view
            Actor::actor    const & player = GLOBAL::GetPlayer();
            auto            const & cameraPos = player.GetPosition();
            auto            const & cameraFront = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetFront();
            auto            const & cameraUp = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetUp();
            auto            const & fov = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetFOV();
            glm::mat4       const   view{ glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp) };
            pObjShaderProgram->setMat4("view", view);
            pObjShaderProgram->setVec3("viewPosition", cameraPos);

            // spotLight
            pObjShaderProgram->setVec3("spotLight.position", cameraPos);
            pObjShaderProgram->setVec3("spotLight.direction", cameraFront);
            pObjShaderProgram->setVec3("spotLight.ambient", glm::vec3{ 0.0f, 0.0f, 0.0f });
            pObjShaderProgram->setVec3("spotLight.diffuse", glm::vec3{ 1.0f, 1.0f, 1.0f });
            pObjShaderProgram->setVec3("spotLight.specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
            pObjShaderProgram->setFloat("spotLight.constant", 1.0f);
            pObjShaderProgram->setFloat("spotLight.linear", 0.09);
            pObjShaderProgram->setFloat("spotLight.quadratic", 0.032);
            pObjShaderProgram->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            pObjShaderProgram->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            // projection
            // TODO change to camera
            glm::mat4 const projection{ glm::perspective(glm::radians(fov), 1600.0f / 900.0f, 0.1f, 100.0f) };
            pObjShaderProgram->setMat4("projection", projection);
            // Draw current VAO
            glBindVertexArray(VAO);
            for (int i = 0; i != 10; ++i)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, glm::radians(5.f * i) * (float)glfwGetTime(), glm::vec3(0.7f * i, 0.3f * i, 5.f * i));
                pObjShaderProgram->setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // *********************************************
            /// Drawing light!!
            // *********************************************
            pLightShaderProgram->Use();
            pLightShaderProgram->setMat4("view", view);
            pLightShaderProgram->setMat4("projection", projection);

            glBindVertexArray(lightVAO);
            for (unsigned int i = 0; i < 4; i++)
            {
                glm::mat4 light = glm::mat4(1.0f);
                light = glm::translate(light, pointLightPositions[i]);
                light = glm::scale(light, glm::vec3(0.2f)); // Make it a smaller cube
                pLightShaderProgram->setMat4("model", light);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // *********************************************

            win.Draw();
        }

        auto delta_time = glfwGetTime() - prev_time;
        std::cout << "TIMING: " << delta_frame / delta_time << std::endl;

    }

    return 0;
}