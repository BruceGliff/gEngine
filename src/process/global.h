#pragma once

// forward declarations
namespace NSActor {
    class actor;
} //namespace NSActor
namespace NSResources {
    class glWindow;
    class ResourcesManager;
} //namespace NSResources
namespace NSScene {
    class Scene;
} //namespace NSScene

namespace NSDebug {
    class Logger;
} //namespace NSDebug

namespace GLOBAL {
    // Init all program properties: window, resourseMgr, scene, glad
    void Initialize(char const* path_to_exec, int win_width, int win_height, char const* win_name);

    // Return current active ResourceManager
    NSResources::ResourcesManager& GetResManager();
    // Return current active Window
    NSResources::glWindow& GetWindow();
    // Return current Scene
    NSScene::Scene & GetScene();
    
    // TODO make SetPlayer and player_wrap template T
    // Set actor as curent playable object
    void SetPlayer(NSActor::actor * actor);

    // Get current playable object
    NSActor::actor & GetPlayer();

    NSDebug::Logger& GetLogger();
} // namespace GLOBAL