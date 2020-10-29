#include "global.h"
#include "../actor/player_wrap.h"

// GLOBAL object which uniq during the program
Actor::player_wrap PLAYER{};

void GLOBAL::BeginPlay()
{
	PLAYER.construct();
}

Actor::actor_base& GLOBAL::GetPlayer()
{
	return PLAYER.GetPlayer();
}
