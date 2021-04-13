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
    // TODO move shader program to actor?staticMesh?
    auto pObjShaderProgram = resMng.loadShaders("objShader", SHADER_PATH + "stencil/model.vs", SHADER_PATH + "stencil/model.fs");
    if (!pObjShaderProgram->IsCompiled())
    {
        // TODO Check as it should be in global destructor
        glfwTerminate();
        gERROR("Creating objShader program in main");
    }
    
    Component::StaticMesh* bp_mesh = new Component::StaticMesh{ resMng.loadModel<Model::Model3D>("backpack", "res/models/backpack/backpack.obj") };
    std::vector<Renderer::TextureGL*> textures = {resMng.loadTexture("res/textures/windows_texture.png", Renderer::ETextureType::DIFFUSE)};
    Component::StaticMesh* win_mesh = new Component::StaticMesh{ resMng.loadModel<Model::Plane>(textures) };
    win_mesh->SetShaderProgram(pObjShaderProgram);
    bp_mesh->SetShaderProgram(pObjShaderProgram);
    auto & obj = *Scene.Spawn<Actor::actor>();
    obj.AttachComponent("mesh", win_mesh).SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });
    obj.SetPosition({10,0,0});
    Scene.Spawn<Actor::actor>()->AttachComponent("mesh1", bp_mesh);


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

        Scene.Process();
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
