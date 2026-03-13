#pragma once

#include "Pathfinding/player/Player.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/managers/MapManager.hpp"

class App
{
public:
    App();    

    void run(VisualizationType visualizationType);

private:
    std::unique_ptr<Player> player;
    AppState appState;
    MapManager mapManager;

    void processAppStateEvent(AppStateEvent event);
};
