#include "scene_wrap.h"
#include "scene.h"

#include "../debug/debug.h"

using namespace NSScene;

void scene_wrap::construct() {
    static bool isExists = 0;
    if (!isExists) {
        curr_scene = new Scene{};
        isExists = true;
        return;
    }
    gWARNING("Attempt to create another scene");
}

Scene & scene_wrap::GetScene() {
    if (curr_scene)
        return *curr_scene;
    gERROR("Attemp to get null scene");
}
Scene const & scene_wrap::GetScene() const {
    if (curr_scene)
        return *curr_scene;
    gERROR("Attemp to get null scene");
}

scene_wrap::~scene_wrap() {
    delete curr_scene;
}
