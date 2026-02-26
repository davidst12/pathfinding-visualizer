#pragma once

#include <set>

#include "Pathfinding/app/AppStateEvent.hpp"

struct ScreenResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
    std::set<int> optionsSelected = {};
};