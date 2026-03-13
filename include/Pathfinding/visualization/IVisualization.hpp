#pragma once

#include <map>
#include <vector>

#include "Pathfinding/algorithms/AlgorithmResult.hpp"
#include "Pathfinding/visualization/ScreenResult.hpp"

class IVisualization
{
public:
    IVisualization() = default;
    virtual ~IVisualization() = default;

    virtual BasicScreenResult        displayHome() = 0;
    virtual TestModeSelectionResult  displayTestModeSelectionScreen() = 0;
    virtual AlgorithmSelectionResult displayAlgorithmSelectionScreen(bool allow_multiple_selection = false) = 0;
    virtual MapSelectionResult       displayMapSelectionScreen(std::map<std::string, Grid> maps) = 0;
    virtual ExecutionSelectionResult displayExecutionSelectionScreen() = 0;
    virtual BasicScreenResult        displaySimulationScreen(std::vector<AlgorithmResult> results, bool wait_for_input = true) = 0;
};