#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Pathfinding/algorithms/AlgorithmResult.hpp"
#include "Pathfinding/player/AlgorithmPreparation.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/visualization/ScreenResult.hpp"
#include "Pathfinding/visualization/SelectionText.hpp"

class Visualization
{
public:       

    Visualization();

    BasicScreenResult        displayHome();
    TestModeSelectionResult  displayTestModeSelectionScreen();
    AlgorithmSelectionResult displayAlgorithmSelectionScreen(bool allow_multiple_selection = false);
    MapSelectionResult       displayMapSelectionScreen(std::map<std::string, Grid> maps);
    ExecutionSelectionResult displayExecutionSelectionScreen();
    BasicScreenResult        displaySimulationScreen(std::vector<AlgorithmResult> results, bool wait_for_input = true);

private:
    sf::RenderWindow window;
    sf::Font font;

    void displayOptionsScreen(SelectionText& optionsMenuText);

    sf::VertexArray gridToVertexArray(Grid& grid, int algorithmIndex, bool is_algorithm_running);
    sf::VertexArray pathToVertexArray(AlgorithmResult result, int algorithmIndex);
    sf::Color getNodeColor(Node* node, bool is_algorithm_running);

    sf::Text statisticsToText(AlgorithmResult result, int algorithmIndex);
};  