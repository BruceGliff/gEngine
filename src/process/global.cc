#include "global.h"

#include "../actor/player_wrap.h"
#include "../manager/EnvironmentHandler_wrap.h"

#include "../actor/actor.h"
#include "../manager/ResourceManager.h"
#include "../window/window_base.h"

#include <iostream>

// GLOBAL object which unique during the program
Actor::player_wrap PLAYER{};
// enviroment with window and resourcesMGR context
Resources::EnvironmentHandler_wrap ENV_MGR{};

// TODO WARNING!! maybe RES_MGR should be deleted before window
void GLOBAL::Initialize(char const * path_to_exec, int win_width, int win_height, char const * win_name)
{
	ENV_MGR.construct(win_width, win_height, win_name, path_to_exec);

	PLAYER.construct();

	/* Initialize glad */
	if (!gladLoadGL())
	{
		std::cerr << "Cannot initialize GLAD" << std::endl;
		throw std::runtime_error{ "ERR:: Cannot initialize GLAD!" };
	}

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL ver: " << glGetString(GL_VERSION) << std::endl;
}

Actor::actor& GLOBAL::GetPlayer()
{
	return PLAYER.GetPlayer();
}

Resources::ResourcesManager& GLOBAL::GetResManager()
{
	return ENV_MGR.GetMenager();
}

Resources::glWindow& GLOBAL::GetWindow()
{
	return ENV_MGR.GetWindow();
}
