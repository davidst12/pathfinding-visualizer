#include "Pathfinding/player/Player.hpp"

#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/algorithms/DFS.hpp"
#include "Pathfinding/algorithms/Dijkstra.hpp"
#include "Pathfinding/algorithms/AStar.hpp"
#include "Pathfinding/utils/maps.hpp"

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

AppStateEvent Player::handleMainMenuState()
{
    return visualization.displayMainMenu().state_event;
}

AppStateEvent Player::handleSelectAlgorithmMenuState()
{
    algorithm.reset();

    ScreenResult screen_result = visualization.displayAlgorithmSelectionScreen();
    switch (screen_result.optionSelected) {
        case 1:
            algorithm = std::make_unique<BFS>();
            break;
        case 2:
            algorithm = std::make_unique<DFS>();
            break;
        case 3:
            algorithm = std::make_unique<Dijkstra>();
            break;
        case 4:
            algorithm = std::make_unique<AStar>();
            break;
        default:
            break;
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectMapMenuState() {
    grid.reset();

    ScreenResult screen_result = visualization.displayMapSelectionScreen();
    switch (screen_result.optionSelected) {
        case 1:
            grid = std::make_shared<Grid>(map1);
            break;
        case 2:
            grid = std::make_shared<Grid>(map2);
            break;
        case 3:
            grid = std::make_shared<Grid>(map3);
            break;
        case 4:
            grid = std::make_shared<Grid>(map4);
            break;
        case 5:
            grid = std::make_shared<Grid>(map5);
            break;
        case 6:
            grid = std::make_shared<Grid>(map6);
            break;
        default:
            break;
    }

    return screen_result.state_event;
}

AppStateEvent Player::handleSelectExecutionMenuState() {
    ScreenResult screen_result = visualization.displayExecutionSelectionScreen();
    switch (screen_result.optionSelected) {
        case 1:
            executionMode = AlgorithmExecutionMode::Instant;
            break;
        case 2:
            executionMode = AlgorithmExecutionMode::StepByStep;
            break;
        default:
            break;
    }

    return screen_result.state_event;
}

AppStateEvent Player::handlePlayingState()
{
    ScreenResult screen_result;
    if (executionMode == AlgorithmExecutionMode::Instant) {
        AlgorithmResult result = algorithm->runAlgorithm(*grid.get());
        screen_result = visualization.displayPlayingScreen(result);
    } else if (executionMode == AlgorithmExecutionMode::StepByStep) {
        algorithm->setGrid(*grid.get());
        AlgorithmResult result;
        screen_result;
        do {
            result = algorithm->runStepAlgorithm();
            screen_result = visualization.displayPlayingScreen(result);
        } while(screen_result.state_event == AppStateEvent::Continue && result.state == AlgorithmState::RUNNING);
    }

    return screen_result.state_event;
}