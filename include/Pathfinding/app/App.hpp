#pragma once

#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/managers/MapManager.hpp"
#include "Pathfinding/player/Player.hpp"

class App {
   public:
    App(std::unique_ptr<IPlayer> player, std::unique_ptr<IMapManager> map_manager);

    void run();

   private:
    std::unique_ptr<IPlayer> m_player;
    std::unique_ptr<IMapManager> m_map_manager;
    AppState m_app_state;

    void processAppStateEvent(AppStateEvent event);
};
