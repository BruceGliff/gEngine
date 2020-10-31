#include "global.h"

#include "../actor/player_wrap.h"
#include "../manager/ResourceManager_wrap.h"
#include "../window/window_wrap.h"

#include "../actor/actor.h"
#include "../manager/ResourceManager.h"
#include "../window/window_base.h"

// GLOBAL object which unique during the program
Actor::player_wrap PLAYER{};
Resources::windows_wrap WINDOW{};
Resources::ResourcesManager_wrap RES_MGR{};

// TODO WARNING!! maybe RES_MGR should be deleted before window
void GLOBAL::Initialize(char const * path_to_exec, int win_width, int win_height, char const * win_name)
{
	// FIRST: Construct Window within GLFW context!
	WINDOW.construct(win_width, win_height, win_name);
	// SECOND: Construct Resource mgr, what obtain resources at program
	RES_MGR.construct(path_to_exec);

	PLAYER.construct();
}

Actor::actor& GLOBAL::GetPlayer()
{
	return PLAYER.GetPlayer();
}

Resources::ResourcesManager& GLOBAL::GetResManager()
{
	return RES_MGR.GetMenager();
}

Resources::glWindows& GLOBAL::GetWindow()
{
	return WINDOW.GetWindow();
}
