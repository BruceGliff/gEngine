#include "global.h"

#include "debug/logger.h"
#include "debug/debug.h"

#include "manager/EnvironmentHandler_wrap.h"
#include "scene/scene_wrap.h"
#include "actor/player_wrap.h"

#include "manager/ResourceManager.h"
#include "window/window_base.h"
#include "scene/scene.h"

// GLOBAL enviroment with window and resourcesMGR context
NSResources::EnvironmentHandler_wrap ENV_MGR{};
// GLOBAL scene which is unique during the program
NSScene::scene_wrap SCENE{};
// GLOBAL player
NSActor::player_wrap PLAYER{};
// log class respinsible for collecting errors
NSDebug::Logger LOG{};

// TODO WARNING!! maybe RES_MGR should be deleted before window
void GLOBAL::Initialize(char const * path_to_exec, int win_width, int win_height, char const * win_name) {
    ENV_MGR.construct(win_width, win_height, win_name, path_to_exec);
    /* Initialize glad */
    if (!gladLoadGL())
        gERROR("Cannot initialize GLAD");
    SCENE.construct();

    gMESSAGE(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    gMESSAGE(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}
NSResources::ResourcesManager& GLOBAL::GetResManager() {
    return ENV_MGR.GetMenager();
}
NSResources::glWindow& GLOBAL::GetWindow() {
    return ENV_MGR.GetWindow();
}
NSScene::Scene& GLOBAL::GetScene() {
    return SCENE.GetScene();
}
NSDebug::Logger& GLOBAL::GetLogger() {
    return LOG;
}
void GLOBAL::SetPlayer(NSActor::actor * actor) {
    PLAYER.SetPlayer(actor);
}
NSActor::actor& GLOBAL::GetPlayer() {
    return PLAYER.GetPlayer();
}
