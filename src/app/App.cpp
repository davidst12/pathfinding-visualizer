#include "Pathfinding/app/App.hpp"

App::App(std::unique_ptr<IPlayer> player, std::unique_ptr<IMapManager> map_manager)
    : player(std::move(player))
    , mapManager(std::move(map_manager)) {}

void App::run() {

    appState = AppState::MainMenu;
    AppStateEvent event;

    mapManager->loadAllMaps("assets/maps/");
    player->setAvailableMaps(mapManager->getAllMaps());

    while(true) {
        event = player->processAppState(appState);
        processAppStateEvent(event);
        
        if (appState == AppState::Exit) {
            break;
        }
    }
}

void App::processAppStateEvent(AppStateEvent event) {
    if(event == AppStateEvent::Exit) {
        appState = AppState::Exit;
        return;
    } else if (event == AppStateEvent::Continue) {
        switch(appState) {
            case AppState::MainMenu:
                appState = AppState::SelectTestModeMenu;
                break;
            case AppState::SelectTestModeMenu:
                appState = AppState::SelectAlgorithmMenu;
                break;
            case AppState::SelectAlgorithmMenu:
                appState = AppState::SelectMapMenu;
                break;
            case AppState::SelectMapMenu:
                appState = AppState::SelectExecutionMenu;
                break;
            case AppState::SelectExecutionMenu:
                appState = AppState::Playing;
                break;
            case AppState::Playing:
                appState = AppState::MainMenu;
                break;
            case AppState::Exit:
                break;
        }
    } else if(event == AppStateEvent::Back) {
        switch(appState) {
            case AppState::MainMenu:
                appState = AppState::Exit;
                break;
            case AppState::SelectTestModeMenu:
                appState = AppState::MainMenu;
                break;
            case AppState::SelectAlgorithmMenu:
                appState = AppState::SelectTestModeMenu;
                break;
            case AppState::SelectMapMenu:
                appState = AppState::SelectAlgorithmMenu;
                break;
            case AppState::SelectExecutionMenu:
                appState = AppState::SelectMapMenu;
                break;
            case AppState::Playing:
                appState = AppState::SelectExecutionMenu;
                break;
            case AppState::Exit:
                break;
        }
    }
}