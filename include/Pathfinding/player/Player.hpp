#pragma once

#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/player/IPlayer.hpp"
#include "Pathfinding/visualization/VisualizationType.hpp"
#include "Pathfinding/visualization/sfml/SfmlVisualization.hpp"
#include "Pathfinding/visualization/terminal/TerminalVisualization.hpp"

class Player : public IPlayer {
   public:
    Player(std::unique_ptr<IVisualization> visualization);

    AppStateEvent processAppState(AppState state) override;
    void setAvailableMaps(std::map<std::string, Grid> maps) override;

   private:
    std::unique_ptr<IVisualization> m_visualization;
    std::vector<std::unique_ptr<IAlgorithm>> m_algorithms;
    std::map<std::string, Grid> m_maps;
    std::shared_ptr<Grid> m_grid;
    AlgorithmExecutionMode m_execution_mode;
    AlgorithmTestMode m_test_mode;

    AppStateEvent handleMainMenuState();
    AppStateEvent handleSelectTestModeMenuState();
    AppStateEvent handleSelectAlgorithmMenuState();
    AppStateEvent handleSelectMapMenuState();
    AppStateEvent handleSelectExecutionMenuState();
    AppStateEvent handlePlayingState();
};
