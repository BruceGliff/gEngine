#include "player_wrap.h"
#include <iostream>
#include <exception>

Actor::player_wrap::player_wrap() noexcept
{}

void Actor::player_wrap::construct()
{
	static int counter = 0;
	if (!counter)
		curr_actor = new actor_base{};
	else
		std::cout << "WARN:: creating new actor" << std::endl;
	++counter;
}

Actor::actor_base& Actor::player_wrap::GetPlayer()
{
	if (!curr_actor)
	{
		std::cerr << "ERR:: getting null player!" << std::endl;
		throw std::runtime_error{ "ERR:: gettin null player!" };
	}
	return *curr_actor;
}

Actor::actor_base const& Actor::player_wrap::GetPlayer() const
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
