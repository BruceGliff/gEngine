#pragma once
#include <memory>


// forward declarations
namespace Actor
{
	class actor;
}
namespace Resources
{
	class glWindow;
	class ResourcesManager;
}
namespace Scene
{
	class Scene;
}

namespace Debug
{
	class Logger;
}

namespace GLOBAL
{
	// Init all program properties: window, resourseMgr, scene, glad
	void Initialize(char const* path_to_exec, int win_width, int win_height, char const* win_name);

	// Return current active ResourceManager
	Resources::ResourcesManager& GetResManager();
	// Return current active Window
	Resources::glWindow& GetWindow();
	// Return current Scene
	Scene::Scene & GetScene();
	
	// TODO make SetPlayer and player_wrap template T
	// Set actor as curent playable object
	void SetPlayer(std::shared_ptr<Actor::actor> const & actor);

	// Get current playable object
	Actor::actor & GetPlayer();

	Debug::Logger& GetLogger();
}