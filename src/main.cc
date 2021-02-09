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
#include "actor/components/staticMesh.h"
#include "debug/debug.h"



std::string const SHADER_PATH{ "res/shaders/" };

int main(int argc, char * argv[])
{        
    GLOBAL::Initialize(argv[0], 1600, 900, "gEngine");

    Resources::ResourcesManager& resMng = GLOBAL::GetResManager();
    auto pObjShaderProgram = resMng.loadShaders("objShader", SHADER_PATH + "model.vs", SHADER_PATH + "model.fs");
    if (!pObjShaderProgram->IsCompiled())
    {
        glfwTerminate();
        gERROR("Creating objShader program in main");
    }


    Actor::actor backpack{};
    backpack.AttachComponent("mesh", new Component::StaticMesh{resMng.getPathToExucutable() / "res/models/backpack/backpack.obj"});

    // Easiest benchmark
    int delta_frame = 0;
    auto const prev_time = glfwGetTime();

    Resources::glWindow& win = GLOBAL::GetWindow();
    glEnable(GL_DEPTH_TEST);
    while (!win.ProcessInput())
    {
        ++delta_frame;

        /* Render here */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        pObjShaderProgram->Use();
        //Change camera position
        // TODO think about view
        Actor::actor    const & player = GLOBAL::GetPlayer();
        auto            const & cameraPos = player.GetPosition();
        auto            const & cameraFront = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetFront();
        auto            const & cameraUp = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetUp();
        auto            const & fov = static_cast<Component::camera*>(GLOBAL::GetPlayer().GetComponent("camera"))->GetFOV();
        glm::mat4       const   view{ glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp) };
        pObjShaderProgram->setMat4("view", view);

        // projection
        // TODO change to camera
        glm::mat4 const projection{ glm::perspective(glm::radians(fov), 1600.0f / 900.0f, 0.1f, 100.0f) };
        pObjShaderProgram->setMat4("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));	// it's a bit too big for our scene, so scale it down
        pObjShaderProgram->setMat4("model", model);
        //ourModel.Draw(*pObjShaderProgram);
        backpack.Process(*pObjShaderProgram, );

        win.Draw();
    }

    auto delta_time = glfwGetTime() - prev_time;
    std::cout << "TIMING: " << delta_frame / delta_time << std::endl;


#ifdef gWINDOWS
    std::cout << "WARN:: Win special" << std::endl;
    system("pause");
#endif // gWINDOWS
#ifdef gUNIX
    std::cout << "WARN:: Unix special" << std::endl;
#endif // gUNIX

    return 0;
}