#include "player_wrap.h"
#include "actor.h"

#include "../debug/debug.h"

#include <iostream>

using namespace NSActor;

actor& player_wrap::GetPlayer() {
    if (isExist)
        return *curr_actor;
    gERROR("Getting null player!");
}

actor const& player_wrap::GetPlayer() const {
    if (isExist)
        return *curr_actor;
    gERROR("Getting null player!");
}


void player_wrap::SetPlayer(actor * actor) {
    curr_actor = actor;
    isExist = true;
}

