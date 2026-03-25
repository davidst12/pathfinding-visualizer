#pragma once

#include <set>

#include "Pathfinding/app/AppStateEvent.hpp"

struct BasicScreenResult {
    AppStateEvent state_event = AppStateEvent::kUnhandled;
};

struct TestModeSelectionResult {
    AppStateEvent state_event = AppStateEvent::kUnhandled;
    AlgorithmTestMode test_mode = AlgorithmTestMode::kUnknown;
};

struct AlgorithmSelectionResult {
    AppStateEvent state_event = AppStateEvent::kUnhandled;
    std::set<AlgorithmType> algorithms_selected;
};

struct MapSelectionResult {
    AppStateEvent state_event = AppStateEvent::kUnhandled;
    std::string map_name;
};

struct ExecutionSelectionResult {
    AppStateEvent state_event = AppStateEvent::kUnhandled;
    AlgorithmExecutionMode execution_mode = AlgorithmExecutionMode::kUnknown;
};