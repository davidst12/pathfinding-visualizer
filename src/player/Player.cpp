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
        visualization = std::make_unique<TerminalVisualization>();
        break;
    case VisualizationType::Sfml:
        visualization = std::make_unique<SfmlVisualization>();
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
    return visualization->displayHome().state_event;
}

AppStateEvent Player::handleSelectTestModeMenuState()
{
    TestModeSelectionResult screen_result = visualization->displayTestModeSelectionScreen();
    testMode = screen_result.test_mode;

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectAlgorithmMenuState()
{
    for (auto& algorithm : algorithms) algorithm.reset();
    algorithms.clear();

    AlgorithmSelectionResult screen_result = visualization->displayAlgorithmSelectionScreen(testMode == AlgorithmTestMode::MultipleAlgorithms);
    for (auto option : screen_result.algorithms_selected) {
        switch (option) {
            case AlgorithmType::BFS:
                algorithms.push_back(std::make_unique<BFS>());
                break;
            case AlgorithmType::DFS:
                algorithms.push_back(std::make_unique<DFS>());
                break;
            case AlgorithmType::Dijkstra:
                algorithms.push_back(std::make_unique<Dijkstra>());
                break;
            case AlgorithmType::AStar:
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

    MapSelectionResult screen_result = visualization->displayMapSelectionScreen(maps);
    if (screen_result.state_event == AppStateEvent::Continue) {
        grid = std::make_shared<Grid>(maps[screen_result.map_name]);
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectExecutionMenuState() {
    ExecutionSelectionResult screen_result = visualization->displayExecutionSelectionScreen();
    executionMode = screen_result.execution_mode;

    return screen_result.state_event;
}

AppStateEvent Player::handlePlayingState()
{
    BasicScreenResult screen_result;

    std::vector<AlgorithmResult> results;

    for(auto& algorithm : algorithms) algorithm->prepare(*grid.get());

    if (executionMode == AlgorithmExecutionMode::Instant) {
        for(auto& algorithm : algorithms) results.push_back(algorithm->solve());
        screen_result = visualization->displaySimulationScreen(results);
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
            screen_result = visualization->displaySimulationScreen(results);

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
            screen_result = visualization->displaySimulationScreen(results, !some_algorithm_is_running);
            if(screen_result.state_event == AppStateEvent::Continue && some_algorithm_is_running) {
                results.clear();
                for(auto& algorithm : algorithms) results.push_back(algorithm->solve());
                screen_result = visualization->displaySimulationScreen(results);
                break;
            }
            if (some_algorithm_is_running) std::this_thread::sleep_for(std::chrono::milliseconds(600));

        } while(screen_result.state_event != AppStateEvent::Exit && some_algorithm_is_running);
    }

    return screen_result.state_event;
}