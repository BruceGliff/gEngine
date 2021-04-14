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
    auto pObjShaderProgram = resMng.loadShaders("DefaultObjShader", SHADER_PATH + "blending/model.vs", SHADER_PATH + "blending/model.fs");
    if (!pObjShaderProgram->IsCompiled())
    {
        // TODO Check as it should be in global destructor
        glfwTerminate();
        gERROR("Creating objShader program in main");
    }
    
    std::vector<Renderer::TextureGL*> grass_texture = {resMng.loadTexture("res/textures/windows_texture.png", Renderer::ETextureType::DIFFUSE)};
    for (int i = 0; i != 10;  ++i) {
        Scene.Spawn<Actor::actor>()->
                            AttachComponent<Component::StaticMesh>("grass", resMng.loadModel<Model::Plane>(grass_texture)).
                            SetPosition({2 * i, 0, (i % 3) * 1.4 + 2});
    }

    Actor::actor player_actor{};
    player_actor.AttachComponent("camera", new Component::camera{});
    auto pPlayer = Scene.Attach(player_actor);
    GLOBAL::SetPlayer(pPlayer);


    // Easiest benchmark
    int delta_frame = 0;
    auto const prev_time = glfwGetTime();

    Resources::glWindow& win = GLOBAL::GetWindow();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
