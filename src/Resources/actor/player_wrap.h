#pragma once
#include "actor.h"

namespace Actor
{
	// singletop that represent current used playable class
	class player_wrap final
	{
		actor_base* curr_actor = nullptr;

	public:
		player_wrap() noexcept;
		void construct();
		player_wrap(player_wrap const &) = delete;
		player_wrap(player_wrap &&) = delete;
		player_wrap operator=(player_wrap const&) = delete;
		player_wrap operator=(player_wrap&&) = delete;

		actor_base& GetPlayer();
		actor_base const& GetPlayer() const;

		~player_wrap();
	};
	

	
}
extern Actor::player_wrap PLAYER;