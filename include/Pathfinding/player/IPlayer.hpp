#pragma once

#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/visualization/VisualizationType.hpp"
#include "Pathfinding/visualization/sfml/SfmlVisualization.hpp"
#include "Pathfinding/visualization/terminal/TerminalVisualization.hpp"

class IPlayer {
   public:
    virtual ~IPlayer() = default;

    virtual AppStateEvent processAppState(AppState state) = 0;
    virtual void setAvailableMaps(std::map<std::string, Grid> maps) = 0;

   protected:
    IPlayer() = default;
};