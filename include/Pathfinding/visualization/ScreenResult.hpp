#pragma once

#include <set>

#include "Pathfinding/app/AppStateEvent.hpp"

struct BasicScreenResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
};

struct TestModeSelectionResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
    AlgorithmTestMode test_mode = AlgorithmTestMode::Unknown;
};

struct AlgorithmSelectionResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
    std::set<AlgorithmType> algorithms_selected = {};
};

struct MapSelectionResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
    std::string map_name;
};

struct ExecutionSelectionResult
{
    AppStateEvent state_event = AppStateEvent::Unhandled;
    AlgorithmExecutionMode execution_mode = AlgorithmExecutionMode::Unknown;
};