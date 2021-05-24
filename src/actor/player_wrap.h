#pragma once

#include <memory>

namespace Actor {

// forward declaration
class actor;

// singleton that represent current used playable class
class player_wrap final {
    Actor::actor * curr_actor {};
    bool isExist {false};

public:
    player_wrap() = default;
    player_wrap(player_wrap const &)            = delete;
    player_wrap(player_wrap &&)                 = delete;
    player_wrap operator=(player_wrap const&)   = delete;
    player_wrap operator=(player_wrap&&)        = delete;

    //  Get current actor
    Actor::actor& GetPlayer();
    //  Get current actor
    Actor::actor const & GetPlayer() const;

    // Set actor as current. Info about previous is lost;
    void SetPlayer(Actor::actor * actor);

    ~player_wrap() {}
};

} // namespace Actor