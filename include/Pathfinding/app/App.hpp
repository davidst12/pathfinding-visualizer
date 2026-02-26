#pragma once

#include "Pathfinding/player/Player.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"

class App
{
public:
    App();    

    void run();

private:
    Player player;
    AppState appState;

    void processAppStateEvent(AppStateEvent event);
};
