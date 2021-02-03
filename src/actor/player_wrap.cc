#include "player_wrap.h"
#include "actor.h"

#include "components/camera.h"
#include "../debug/debug.h"

#include <iostream>

Actor::player_wrap::player_wrap() noexcept
{}

void Actor::player_wrap::construct()
{
	static int counter = 0;
	if (!counter)
	{
		curr_actor = new actor{};
		curr_actor->attach_component("camera", new Component::camera{});
		++counter;
	}
	else
		gWARNING("attempt to create new actor");
}

Actor::actor& Actor::player_wrap::GetPlayer()
{
	if (curr_actor)
	{
		return *curr_actor;
	}
	
	gERROR("getting null player!");
}

Actor::actor const& Actor::player_wrap::GetPlayer() const
{
	if (curr_actor)
	{
		return *curr_actor;
	}

	gERROR("getting null player!");
}

Actor::player_wrap::~player_wrap()
{
	if (!curr_actor)
		delete curr_actor;
}
