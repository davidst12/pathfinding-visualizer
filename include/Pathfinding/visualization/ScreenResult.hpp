#pragma once

#include "Pathfinding/app/AppStateEvent.hpp"

struct ScreenResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
    int optionSelected = 0;;
};