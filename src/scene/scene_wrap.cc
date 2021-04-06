#include "scene_wrap.h"
#include "scene.h"

#include "debug/debug.h"

void Scene::scene_wrap::construct()
{
    static bool isExists = 0;
    if (!isExists)
    {
        curr_scene = new Scene{};
        isExists = true;
        return;
    }

    gWARNING("Attempt to create another scene");
}


Scene::Scene & Scene::scene_wrap::GetScene()
{
    if (curr_scene)
        return *curr_scene;

    gERROR("Attemp to get null scene");
}
Scene::Scene const & Scene::scene_wrap::GetScene() const
{
    if (curr_scene)
        return *curr_scene;

    gERROR("Attemp to get null scene");
}

Scene::scene_wrap::~scene_wrap()
{
    delete curr_scene;
}
