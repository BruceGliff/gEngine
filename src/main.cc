#include <iostream>
#include <cmath>

#include "process/global.h"
#include "manager/ResourceManager.h"
#include "renderer/ShaderProgram.h"
#include "renderer/TextureGL.h"
#include "window/window_base.h"
#include "actor/actor.h"
#include "scene/scene.h"
#include "actor/components/camera.h"
#include "actor/components/staticMesh.h"
#include "geometry/geometry_base.h"
#include "debug/debug.h"



std::string const SHADER_PATH{ "res/shaders/" };

int main(int argc, char * argv[])
{        
    GLOBAL::Initialize(argv[0], 1600, 900, "gEngine");
    auto& Scene = GLOBAL::GetScene();

    Resources::ResourcesManager& resMng = GLOBAL::GetResManager();
    auto pObjShaderProgram = resMng.loadShaders("objShader", SHADER_PATH + "model.vs", SHADER_PATH + "model.fs");
    if (!pObjShaderProgram->IsCompiled())
    {
        // TODO Check as it should be in global destructor
        glfwTerminate();
        gERROR("Creating objShader program in main");
    }

    // backpack
    Actor::actor backpack{};
    backpack.AttachComponent("mesh", new Component::StaticMesh{"backpack", "res/models/backpack/backpack.obj"});


    Actor::actor backPackRoot{};
    backPackRoot.AttachComponent("mesh", new Component::StaticMesh{ "backpack" });
    backPackRoot.SetPosition(glm::vec3{ 10.f, 10.f, 10.f });

    backpack.AttachComponent("actor", new Actor::actor{ std::move(backPackRoot) });

    //auto aa = Scene.Attach(backPackRoot);
    auto a = Scene.Attach(backpack);

    Actor::actor player_actor{};
    player_actor.AttachComponent("camera", new Component::camera{});
    auto pPlayer = Scene.Attach(player_actor);
    GLOBAL::SetPlayer(pPlayer);


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

        for (auto&& x : Scene)
        {  
            x.second->Process(*pObjShaderProgram, Geometry::Transformation{});
        }
        i = 0;

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