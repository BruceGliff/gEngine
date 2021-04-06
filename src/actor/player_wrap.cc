#include "player_wrap.h"
#include "actor.h"

#include "debug/debug.h"

#include <iostream>


Actor::actor& Actor::player_wrap::GetPlayer()
{
	if (isExist)
		return *curr_actor;
	
	gERROR("getting null player!");
}

Actor::actor const& Actor::player_wrap::GetPlayer() const
{
	if (isExist)
		return *curr_actor;

	gERROR("getting null player!");
}


void Actor::player_wrap::SetPlayer(Actor::actor * actor)
{
	curr_actor = actor;
	isExist = true;
}

