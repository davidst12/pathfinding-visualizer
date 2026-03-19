#pragma once

#include "Pathfinding/player/Player.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/managers/MapManager.hpp"

class App
{
public:
    App(std::unique_ptr<IPlayer> player, std::unique_ptr<IMapManager> map_manager);    

    void run();

private:
    std::unique_ptr<IPlayer> player;
    std::unique_ptr<IMapManager> mapManager;
    AppState appState;

    void processAppStateEvent(AppStateEvent event);
};
