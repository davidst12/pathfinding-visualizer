#include "Pathfinding/app/App.hpp"

App::App(std::unique_ptr<IPlayer> player, std::unique_ptr<IMapManager> map_manager)
    : m_player(std::move(player)),
      m_map_manager(std::move(map_manager)),
      m_app_state(AppState::kMainMenu) {}

void App::run() {
    AppStateEvent event = AppStateEvent::kUnhandled;

    m_map_manager->loadAllMaps("assets/maps/");
    m_player->setAvailableMaps(m_map_manager->getAllMaps());

    while (true) {
        event = m_player->processAppState(m_app_state);
        processAppStateEvent(event);

        if (m_app_state == AppState::kExit) {
            break;
        }
    }
}

void App::processAppStateEvent(AppStateEvent event) {
    if (event == AppStateEvent::kExit) {
        m_app_state = AppState::kExit;
        return;
    } else if (event == AppStateEvent::kContinue) {
        switch (m_app_state) {
            case AppState::kMainMenu:
                m_app_state = AppState::kSelectTestModeMenu;
                break;
            case AppState::kSelectTestModeMenu:
                m_app_state = AppState::kSelectAlgorithmMenu;
                break;
            case AppState::kSelectAlgorithmMenu:
                m_app_state = AppState::kSelectMapMenu;
                break;
            case AppState::kSelectMapMenu:
                m_app_state = AppState::kSelectExecutionMenu;
                break;
            case AppState::kSelectExecutionMenu:
                m_app_state = AppState::kPlaying;
                break;
            case AppState::kPlaying:
                m_app_state = AppState::kMainMenu;
                break;
            case AppState::kExit:
                break;
        }
    } else if (event == AppStateEvent::kBack) {
        switch (m_app_state) {
            case AppState::kMainMenu:
                m_app_state = AppState::kExit;
                break;
            case AppState::kSelectTestModeMenu:
                m_app_state = AppState::kMainMenu;
                break;
            case AppState::kSelectAlgorithmMenu:
                m_app_state = AppState::kSelectTestModeMenu;
                break;
            case AppState::kSelectMapMenu:
                m_app_state = AppState::kSelectAlgorithmMenu;
                break;
            case AppState::kSelectExecutionMenu:
                m_app_state = AppState::kSelectMapMenu;
                break;
            case AppState::kPlaying:
                m_app_state = AppState::kSelectExecutionMenu;
                break;
            case AppState::kExit:
                break;
        }
    }
}