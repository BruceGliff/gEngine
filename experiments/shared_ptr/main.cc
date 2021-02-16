#include "scene.h"
#include <stdio.h>
int main()
{
    actor a;
    a.AttachComponent("camera", new camera{}).GetComponentByName<camera>("camera")->id;
    std::cout << a.AttachComponent("camera1", new camera{}).GetComponentByName<camera>("camera1")->id << std::endl;

    std::cout << a.components.size() << std::endl;
    Scene scene;
    auto x = scene.Attach(a);
    mya m;
    m.AttachComponent("camera", new camera);

    Entity en = scene.Attach(m)->GetEntity();
    scene.GetActor<mya>(en)->Process();

    for (auto && inScene : scene)
    {
        inScene.second->Process();
    }

    std::cout << "ASd\n";
    for (auto && inScene : scene)
    {
        inScene.second->dump();
    }



}