#pragma once

#include "Pathfinding/visualization/sfml/SfmlVisualization.hpp"
#include "Pathfinding/visualization/terminal/TerminalVisualization.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/visualization/VisualizationType.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/player/IPlayer.hpp"

class Player : public IPlayer
{
public: 
    Player(std::unique_ptr<IVisualization> visualization);

    AppStateEvent processAppState(AppState state) override;
    void setAvailableMaps(std::map<std::string, Grid> maps) override;

private:
    std::unique_ptr<IVisualization> visualization;
    std::vector<std::unique_ptr<IAlgorithm>> algorithms;
    std::map<std::string, Grid> maps;
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