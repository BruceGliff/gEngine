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
    gMESSAGE("Debug Mode");

    GLOBAL::Initialize(argv[0], 1600, 900, "gEngine");
    auto& Scene = GLOBAL::GetScene();

    Resources::ResourcesManager& resMng = GLOBAL::GetResManager();
    auto pObjShaderProgram = resMng.loadShaders("objShader", SHADER_PATH + "stencil/model.vs", SHADER_PATH + "stencil/model.fs");
    if (!pObjShaderProgram->IsCompiled())
    {
        // TODO Check as it should be in global destructor
        glfwTerminate();
        gERROR("Creating objShader program in main");
    }

    resMng.loadModel("backpack", "res/models/backpack/backpack.obj");
    
    Component::StaticMesh* bp_mesh = new Component::StaticMesh{ "backpack" };
    bp_mesh->SetShaderProgram(pObjShaderProgram);
    Scene.Spawn<Actor::actor>()->AttachComponent("mesh", bp_mesh).SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });

    Component::StaticMesh* bp_mesh1 = new Component::StaticMesh{ "backpack" };
    bp_mesh1->SetShaderProgram(pObjShaderProgram);
    std::shared_ptr<Actor::actor> tmpA = Scene.Spawn<Actor::actor>();
    tmpA->AttachComponent("mesh", bp_mesh1).SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });
    tmpA->SetPosition(glm::vec3{10.f});
    //for (int i = 1; i != 10; ++i)
    //{
    //    Actor::actor tmp;
    //    tmp.AttachComponent("mesh", new Component::StaticMesh{ "backpack" });
    //    tmp.SetPosition({ 10.f * i, 5.f * i, 1.f * i });
    //    a->AttachComponent("actor", new Actor::actor{ std::move(tmp) });
    //    a = a->GetComponentByName<Actor::actor>("actor");
    //}



    Actor::actor player_actor{};
    player_actor.AttachComponent("camera", new Component::camera{});
    auto pPlayer = Scene.Attach(player_actor);
    GLOBAL::SetPlayer(pPlayer);


    // Easiest benchmark
    int delta_frame = 0;
    auto const prev_time = glfwGetTime();

    Resources::glWindow& win = GLOBAL::GetWindow();
    glEnable(GL_DEPTH_TEST);
    // Stencil for bordering
    glEnable(GL_STENCIL_TEST);
    //  In case {KEEP KEEP REPLACE} all object on back will be entirely drawn
    //  In case {KEEP, REPLACE, REPLACE} only border of back object will be drawn
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

    while (!win.ProcessInput())
    {
        ++delta_frame;

        /* Render here */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        for (auto&& x : Scene)
        {  
            x.second->Process(Geometry::Transformation{});
        }

        win.Draw();
    }

    auto delta_time = glfwGetTime() - prev_time;
    std::cout << "TIMING: " << delta_frame / delta_time << std::endl;


#ifdef gWINDOWS
    gMESSAGE("Window special");
    system("pause");
#endif // gWINDOWS

    return 0;
}