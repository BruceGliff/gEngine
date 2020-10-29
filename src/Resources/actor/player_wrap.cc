#include "player_wrap.h"
#include "components/camera.h"
#include <iostream>
#include <exception>

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
		std::cout << "WARN:: attempt to create new actor" << std::endl;
}

Actor::actor& Actor::player_wrap::GetPlayer()
{
	if (!curr_actor)
	{
		std::cerr << "ERR:: getting null player!" << std::endl;
		throw std::runtime_error{ "ERR:: gettin null player!" };
	}
	return *curr_actor;
}

Actor::actor const& Actor::player_wrap::GetPlayer() const
{
	if (!curr_actor)
	{
		std::cerr << "ERR:: getting null player!" << std::endl;
		throw std::runtime_error{ "ERR:: gettin null player!" };
	}
	return *curr_actor;
}

Actor::player_wrap::~player_wrap()
{
	if (!curr_actor)
		delete curr_actor;
}
