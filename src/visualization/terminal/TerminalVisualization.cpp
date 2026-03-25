#include "Pathfinding/visualization/terminal/TerminalVisualization.hpp"

TerminalVisualization::TerminalVisualization() {}

BasicScreenResult TerminalVisualization::displayHome() {
    BasicScreenResult screen_result;

    std::cout << "Welcome to the Pathfinding Visualizer!" << std::endl;
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();

    screen_result.state_event = AppStateEvent::kContinue;

    return screen_result;
}

TestModeSelectionResult TerminalVisualization::displayTestModeSelectionScreen() {
    TestModeSelectionResult screen_result;
    // For simplicity in terminal mode, we will just set the test mode to SingleAlgorithm and
    // continue.
    screen_result.test_mode = AlgorithmTestMode::kSingleAlgorithm;
    screen_result.state_event = AppStateEvent::kContinue;
    return screen_result;
}

AlgorithmSelectionResult TerminalVisualization::displayAlgorithmSelectionScreen(
    bool allow_multiple_selection) {
    AlgorithmSelectionResult screen_result;
    int selection = 0;

    std::string text = "Select the algorithm (Enter option index)\n";
    text += "1. Breadth-First Search (BFS)\n";
    text += "2. Depth-First Search (DFS)\n";
    text += "3. Dijkstra's Algorithm\n";
    text += "4. A* Search\n";
    text += "5. Exit\n";

    std::cout << text << std::endl;

    do {
        selection = std::cin.get();
        switch (selection) {
            case '1':
                screen_result.algorithms_selected.insert(AlgorithmType::kBFS);
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            case '2':
                screen_result.algorithms_selected.insert(AlgorithmType::kDFS);
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            case '3':
                screen_result.algorithms_selected.insert(AlgorithmType::kDijkstra);
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            case '4':
                screen_result.algorithms_selected.insert(AlgorithmType::kAStar);
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            case '5':
                screen_result.state_event = AppStateEvent::kExit;
                break;
            default:
                std::cout << "Invalid selection. Please try again." << std::endl;
                break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');  // Clear the input buffer
    } while (screen_result.state_event == AppStateEvent::kUnhandled);

    return screen_result;
}

MapSelectionResult TerminalVisualization::displayMapSelectionScreen(
    std::map<std::string, Grid> maps) {
    MapSelectionResult screen_result;
    std::vector<std::string> map_names;

    std::string text = "Select the map (Enter option index)\n";
    int index = 1;
    for (auto& [name, grid] : maps) {
        text += std::to_string(index) + ". " + name + "\n";
        text += grid.toString() + "\n\n";
        index++;
        map_names.push_back(name);
    }
    text += std::to_string(index) + ". Back\n";
    text += std::to_string(++index) + ". Exit\n";

    std::cout << text << std::endl;

    char selection;
    do {
        selection = std::cin.get();
        if (selection >= '1' && selection < map_names.size() + '1') {
            screen_result.map_name = map_names[selection - '1'];
            screen_result.state_event = AppStateEvent::kContinue;
        } else if (selection == '1' + map_names.size()) {
            screen_result.state_event = AppStateEvent::kBack;
        } else if (selection == '2' + map_names.size()) {
            screen_result.state_event = AppStateEvent::kExit;
        } else {
            std::cout << "Invalid selection. Please try again." << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');  // Clear the input buffer
    } while (screen_result.state_event == AppStateEvent::kUnhandled);

    return screen_result;
}

ExecutionSelectionResult TerminalVisualization::displayExecutionSelectionScreen() {
    ExecutionSelectionResult screen_result;

    // For simplicity in terminal mode, we will just set the execution mode to Instant and continue.
    screen_result.execution_mode = AlgorithmExecutionMode::kInstant;
    screen_result.state_event = AppStateEvent::kContinue;

    return screen_result;
}

BasicScreenResult TerminalVisualization::displaySimulationScreen(
    std::vector<AlgorithmResult> results, bool wait_for_input) {
    BasicScreenResult screen_result;

    std::string text = "Simulation Results:\n";
    for (auto& result : results) {
        text += result.grid_resolved->toStringWithPath(result.path) + "\n";
        text += result.toString() + "\n\n";
    }

    text += "Write 'c' to continue, or 'e' to exit...\n";
    std::cout << text << std::endl;

    char selection = 0;
    do {
        selection = std::cin.get();
        switch (selection) {
            case 'c':
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            case 'e':
                screen_result.state_event = AppStateEvent::kExit;
                break;
            default:
                std::cout << "Invalid selection. Please try again." << std::endl;
                break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');  // Clear the input buffer
    } while (screen_result.state_event == AppStateEvent::kUnhandled);

    return screen_result;
}
