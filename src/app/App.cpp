#include "Pathfinding/app/App.hpp"

App::App() : player(VisualizationType::Sfml) {}

void App::run() {

    appState = AppState::MainMenu;
    AppStateEvent event;

    while(true) {
        event = player.processAppState(appState);
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
        }
    } else if(event == AppStateEvent::Back) {
        switch(appState) {
            case AppState::MainMenu:
                appState = AppState::Exit;
                break;
            case AppState::SelectAlgorithmMenu:
                appState = AppState::MainMenu;
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
        }
    }
}