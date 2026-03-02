#include "Pathfinding/player/Player.hpp"

#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/algorithms/DFS.hpp"
#include "Pathfinding/algorithms/Dijkstra.hpp"
#include "Pathfinding/algorithms/AStar.hpp"
#include "Pathfinding/utils/maps.hpp"
#include <thread>

Player::Player(VisualizationType visualization_type)
{
    switch (visualization_type)
    {
    case VisualizationType::Terminal:
        break;
    case VisualizationType::Sfml:
        visualization = Visualization();
        break;
    default:
        throw std::runtime_error("Invalid visualization type");
    }
}

AppStateEvent Player::processAppState(AppState state)
{
    AppStateEvent event;

    switch (state)
    {
    case AppState::MainMenu:
        event = handleMainMenuState();
        break;
    case AppState::SelectTestModeMenu:
        event = handleSelectTestModeMenuState();
        break;
    case AppState::SelectAlgorithmMenu:
        event = handleSelectAlgorithmMenuState();
        break;
    case AppState::SelectMapMenu:
        event = handleSelectMapMenuState();
        break;
    case AppState::SelectExecutionMenu:
        event = handleSelectExecutionMenuState();
        break;
    case AppState::Playing:
        event = handlePlayingState();
        break;
    }

    return event;
}

void Player::setAvailableMaps(std::map<std::string, Grid> maps) { 
    this->maps = maps;
}

AppStateEvent Player::handleMainMenuState()
{
    return visualization.displayMainMenu().state_event;
}

AppStateEvent Player::handleSelectTestModeMenuState()
{
    std::vector<std::string> options = {"Select Algorithm Test Mode", "1. Test single algorithm", "2.Compare algorithms"};
    ScreenResult screen_result = visualization.displayAlgorithmTestModeSelectionScreen(options);
    switch (*screen_result.optionsSelected.begin()) {
        case 1:
            testMode = AlgorithmTestMode::SingleAlgorithm;
            break;
        case 2:
        testMode = AlgorithmTestMode::MultipleAlgorithms;
            break;
        default:
            break;
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectAlgorithmMenuState()
{
    for (auto& algorithm : algorithms) algorithm.reset();
    algorithms.clear();

    std::vector<std::string> options = {"Select Algorithm", "1. BFS", "2. DFS", "3. Dijkstra", "4. A*"};
    ScreenResult screen_result = visualization.displayAlgorithmSelectionScreen(options, testMode == AlgorithmTestMode::MultipleAlgorithms);
    for (int option : screen_result.optionsSelected) {
        switch (option) {
            case 1:
                algorithms.push_back(std::make_unique<BFS>());
                break;
            case 2:
                algorithms.push_back(std::make_unique<DFS>());
                break;
            case 3:
                algorithms.push_back(std::make_unique<Dijkstra>());
                break;
            case 4:
                algorithms.push_back(std::make_unique<AStar>());
                break;
            default:
                break;
        }
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectMapMenuState() {
    grid.reset();

    std::vector<Grid> maps_vector;
    for(const auto& [name, grid] : maps) maps_vector.push_back(grid);
    ScreenResult screen_result = visualization.displayMapSelectionScreen("Select Map", maps);
    grid = std::make_shared<Grid>(maps_vector.at(*screen_result.optionsSelected.begin() - 1));

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectExecutionMenuState() {
    std::vector<std::string> options = {"Select Execution mode", "1. Fast", "2. Step by step", "3. Animated"};
    ScreenResult screen_result = visualization.displayExecutionSelectionScreen(options);
    switch (*screen_result.optionsSelected.begin()) {
        case 1:
            executionMode = AlgorithmExecutionMode::Instant;
            break;
        case 2:
            executionMode = AlgorithmExecutionMode::StepByStep;
            break;
        case 3:
            executionMode = AlgorithmExecutionMode::Animated;
            break;
        default:
            break;
    }

    return screen_result.state_event;
}

AppStateEvent Player::handlePlayingState()
{
    ScreenResult screen_result;

    std::vector<AlgorithmResult> results;

    for(auto& algorithm : algorithms) algorithm->prepare(*grid.get());

    if (executionMode == AlgorithmExecutionMode::Instant) {
        for(auto& algorithm : algorithms) results.push_back(algorithm->solve());
        screen_result = visualization.displayPlayingScreen(results);
    } else if (executionMode == AlgorithmExecutionMode::StepByStep) {
        bool some_algorithm_is_running = false;
        do {
            results.clear();
            some_algorithm_is_running = false;
            for(auto& algorithm : algorithms) {
                AlgorithmResult result = algorithm->step();
                results.push_back(result);
                if(result.state == AlgorithmState::RUNNING) some_algorithm_is_running = true;
            }
            screen_result = visualization.displayPlayingScreen(results);

        } while(screen_result.state_event == AppStateEvent::Continue && some_algorithm_is_running);
    } else if (executionMode == AlgorithmExecutionMode::Animated) {
        bool some_algorithm_is_running = false;
        do {
            results.clear();
            some_algorithm_is_running = false;
            for(auto& algorithm : algorithms) {
                AlgorithmResult result = algorithm->step();
                results.push_back(result);
                if(result.state == AlgorithmState::RUNNING) some_algorithm_is_running = true;
            }
            screen_result = visualization.displayPlayingScreen(results, !some_algorithm_is_running);
            if(screen_result.state_event == AppStateEvent::Continue && some_algorithm_is_running) {
                results.clear();
                for(auto& algorithm : algorithms) results.push_back(algorithm->solve());
                screen_result = visualization.displayPlayingScreen(results);
                break;
            }
            if (some_algorithm_is_running) std::this_thread::sleep_for(std::chrono::milliseconds(600));

        } while(screen_result.state_event != AppStateEvent::Exit && some_algorithm_is_running);
    }

    return screen_result.state_event;
}