#pragma once

#include "Pathfinding/visualization/Visualization.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/visualization/VisualizationType.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"

class Player
{
public: 
    Player(VisualizationType visualization_type);

    AppStateEvent processAppState(AppState state);

    void init();

private:
    Visualization visualization;
    std::vector<std::unique_ptr<IAlgorithm>> algorithms;
    std::shared_ptr<Grid> grid;
    AlgorithmExecutionMode executionMode;
    AlgorithmTestMode testMode;

    AppStateEvent handleMainMenuState();
    AppStateEvent handleSelectTestModeMenuState();
    AppStateEvent handleSelectAlgorithmMenuState();
    AppStateEvent handleSelectMapMenuState();
    AppStateEvent handleSelectExecutionMenuState();
    AppStateEvent handlePlayingState();
};