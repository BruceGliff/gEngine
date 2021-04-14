#include "global.h"

#include "debug/logger.h"
#include "debug/debug.h"

#include "manager/EnvironmentHandler_wrap.h"
#include "scene/scene_wrap.h"
#include "actor/player_wrap.h"

#include "manager/ResourceManager.h"
#include "window/window_base.h"
#include "scene/scene.h"

#include <iostream>

// GLOBAL enviroment with window and resourcesMGR context
Resources::EnvironmentHandler_wrap ENV_MGR{};
// GLOBAL scene which is unique during the program
Scene::scene_wrap SCENE{};
// GLOBAL player
Actor::player_wrap PLAYER{};
// log class respinsible for collecting errors
Debug::Logger LOG{};


// TODO WARNING!! maybe RES_MGR should be deleted before window
void GLOBAL::Initialize(char const * path_to_exec, int win_width, int win_height, char const * win_name)
{
	ENV_MGR.construct(win_width, win_height, win_name, path_to_exec);
	/* Initialize glad */
	if (!gladLoadGL())
	{
		gERROR("Cannot initialize GLAD");
	}
	SCENE.construct();

	gMESSAGE(reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	gMESSAGE(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}
Resources::ResourcesManager& GLOBAL::GetResManager()
{
	return ENV_MGR.GetMenager();
}

Resources::glWindow& GLOBAL::GetWindow()
{
	return ENV_MGR.GetWindow();
}

Scene::Scene& GLOBAL::GetScene()
{
	return SCENE.GetScene();
}

Debug::Logger& GLOBAL::GetLogger()
{
	return LOG;
}

void GLOBAL::SetPlayer(Actor::actor * actor)
{
	PLAYER.SetPlayer(actor);
}

Actor::actor& GLOBAL::GetPlayer()
{
	return PLAYER.GetPlayer();
}
