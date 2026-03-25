#pragma once

#include "Pathfinding/visualization/IVisualization.hpp"

class TerminalVisualization : public IVisualization {
   public:
    TerminalVisualization();

    BasicScreenResult displayHome() override;
    TestModeSelectionResult displayTestModeSelectionScreen() override;
    AlgorithmSelectionResult displayAlgorithmSelectionScreen(
        bool allow_multiple_selection = false) override;
    MapSelectionResult displayMapSelectionScreen(std::map<std::string, Grid> maps) override;
    ExecutionSelectionResult displayExecutionSelectionScreen() override;
    BasicScreenResult displaySimulationScreen(std::vector<AlgorithmResult> results,
                                              bool wait_for_input = true) override;
};