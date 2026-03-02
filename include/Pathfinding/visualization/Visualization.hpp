#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Pathfinding/algorithms/AlgorithmResult.hpp"
#include "Pathfinding/player/AlgorithmPreparation.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/visualization/ScreenResult.hpp"

class Visualization
{
public:       

    Visualization();

    ScreenResult displayMainMenu();
    ScreenResult displayAlgorithmTestModeSelectionScreen(std::vector<std::string> options);
    ScreenResult displayAlgorithmSelectionScreen(std::vector<std::string> options, bool allow_multiple_selection = false);
    ScreenResult displayMapSelectionScreen(std::string title, std::map<std::string, Grid> maps);
    ScreenResult displayExecutionSelectionScreen(std::vector<std::string> options);
    ScreenResult displayPlayingScreen(std::vector<AlgorithmResult> results, bool wait_for_input = true);

private:
    sf::RenderWindow window;
    sf::Font font;

    sf::VertexArray gridToVertexArray(Grid& grid, int algorithmIndex, bool is_algorithm_running);
    sf::VertexArray pathToVertexArray(AlgorithmResult result, int algorithmIndex);
    sf::Color getNodeColor(Node* node, bool is_algorithm_running);

    sf::Text statisticsToText(AlgorithmResult result, int algorithmIndex);
};  