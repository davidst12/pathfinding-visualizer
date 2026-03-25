#include "Pathfinding/player/Player.hpp"

#include <thread>

#include "Pathfinding/algorithms/AStar.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/algorithms/DFS.hpp"
#include "Pathfinding/algorithms/Dijkstra.hpp"

Player::Player(std::unique_ptr<IVisualization> visualization)
    : m_visualization(std::move(visualization)) {}

AppStateEvent Player::processAppState(AppState state) {
    AppStateEvent event = AppStateEvent::kUnhandled;

    switch (state) {
        case AppState::kMainMenu:
            event = handleMainMenuState();
            break;
        case AppState::kSelectTestModeMenu:
            event = handleSelectTestModeMenuState();
            break;
        case AppState::kSelectAlgorithmMenu:
            event = handleSelectAlgorithmMenuState();
            break;
        case AppState::kSelectMapMenu:
            event = handleSelectMapMenuState();
            break;
        case AppState::kSelectExecutionMenu:
            event = handleSelectExecutionMenuState();
            break;
        case AppState::kPlaying:
            event = handlePlayingState();
            break;
        case AppState::kExit:
            event = AppStateEvent::kExit;
            break;
    }

    return event;
}

void Player::setAvailableMaps(std::map<std::string, Grid> maps) {
    this->m_maps = maps;
}

AppStateEvent Player::handleMainMenuState() {
    return m_visualization->displayHome().state_event;
}

AppStateEvent Player::handleSelectTestModeMenuState() {
    TestModeSelectionResult screen_result = m_visualization->displayTestModeSelectionScreen();
    m_test_mode = screen_result.test_mode;

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectAlgorithmMenuState() {
    for (auto& algorithm : m_algorithms) algorithm.reset();
    m_algorithms.clear();

    AlgorithmSelectionResult screen_result = m_visualization->displayAlgorithmSelectionScreen(
        m_test_mode == AlgorithmTestMode::kMultipleAlgorithms);
    for (auto option : screen_result.algorithms_selected) {
        switch (option) {
            case AlgorithmType::kBFS:
                m_algorithms.push_back(std::make_unique<BFS>());
                break;
            case AlgorithmType::kDFS:
                m_algorithms.push_back(std::make_unique<DFS>());
                break;
            case AlgorithmType::kDijkstra:
                m_algorithms.push_back(std::make_unique<Dijkstra>());
                break;
            case AlgorithmType::kAStar:
                m_algorithms.push_back(std::make_unique<AStar>());
                break;
            default:
                break;
        }
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectMapMenuState() {
    m_grid.reset();

    MapSelectionResult screen_result = m_visualization->displayMapSelectionScreen(m_maps);
    if (screen_result.state_event == AppStateEvent::kContinue) {
        m_grid = std::make_shared<Grid>(m_maps[screen_result.map_name]);
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectExecutionMenuState() {
    ExecutionSelectionResult screen_result = m_visualization->displayExecutionSelectionScreen();
    m_execution_mode = screen_result.execution_mode;

    return screen_result.state_event;
}

AppStateEvent Player::handlePlayingState() {
    BasicScreenResult screen_result;

    std::vector<AlgorithmResult> results;

    for (auto& algorithm : m_algorithms) algorithm->prepare(*m_grid.get());

    if (m_execution_mode == AlgorithmExecutionMode::kInstant) {
        for (auto& algorithm : m_algorithms) results.push_back(algorithm->solve());
        screen_result = m_visualization->displaySimulationScreen(results);
    } else if (m_execution_mode == AlgorithmExecutionMode::kStepByStep) {
        bool some_algorithm_is_running = false;
        do {
            results.clear();
            some_algorithm_is_running = false;
            for (auto& algorithm : m_algorithms) {
                AlgorithmResult result = algorithm->step();
                results.push_back(result);
                if (result.state == AlgorithmState::kRunning) some_algorithm_is_running = true;
            }
            screen_result = m_visualization->displaySimulationScreen(results);

        } while (screen_result.state_event == AppStateEvent::kContinue &&
                 some_algorithm_is_running);
    } else if (m_execution_mode == AlgorithmExecutionMode::kAnimated) {
        bool some_algorithm_is_running = false;
        do {
            results.clear();
            some_algorithm_is_running = false;
            for (auto& algorithm : m_algorithms) {
                AlgorithmResult result = algorithm->step();
                results.push_back(result);
                if (result.state == AlgorithmState::kRunning) some_algorithm_is_running = true;
            }
            screen_result =
                m_visualization->displaySimulationScreen(results, !some_algorithm_is_running);
            if (screen_result.state_event == AppStateEvent::kContinue &&
                some_algorithm_is_running) {
                results.clear();
                for (auto& algorithm : m_algorithms) results.push_back(algorithm->solve());
                screen_result = m_visualization->displaySimulationScreen(results);
                break;
            }
            if (some_algorithm_is_running)
                std::this_thread::sleep_for(std::chrono::milliseconds(600));

        } while (screen_result.state_event != AppStateEvent::kExit && some_algorithm_is_running);
    }

    return screen_result.state_event;
}