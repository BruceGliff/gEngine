#pragma once

#include <memory>

namespace NSActor {

// forward declaration
class actor;

// singleton that represent current used playable class
class player_wrap final {
    actor * curr_actor {};
    bool isExist {false};

public:
    player_wrap() = default;
    player_wrap(player_wrap const &)            = delete;
    player_wrap(player_wrap &&)                 = delete;
    player_wrap operator=(player_wrap const&)   = delete;
    player_wrap operator=(player_wrap&&)        = delete;

    //  Get current actor
    actor& GetPlayer();
    //  Get current actor
    actor const & GetPlayer() const;

    // Set actor as current. Info about previous is lost;
    void SetPlayer(actor * actor);

    ~player_wrap() {}
};

} // namespace NSActor