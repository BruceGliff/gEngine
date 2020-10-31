#pragma once
// forward declarations
namespace Actor
{
	class actor;
}
namespace Resources
{
	class glWindows;
	class ResourcesManager;
}

namespace GLOBAL
{
	// Init all program properties
	void Initialize(char const* path_to_exec, int win_width, int win_height, char const* win_name);

	// Return current active player
	Actor::actor& GetPlayer();
	// Return current active ResourceManager
	Resources::ResourcesManager& GetResManager();
	// Return current active Window
	Resources::glWindows& GetWindow();
}