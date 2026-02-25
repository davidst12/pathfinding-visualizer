#pragma once

#include <SFML/Graphics.hpp>

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
    ScreenResult displayAlgorithmSelectionScreen();
    ScreenResult displayMapSelectionScreen();
    ScreenResult displayExecutionSelectionScreen();
    ScreenResult displayPlayingScreen(AlgorithmResult result);

private:
    sf::RenderWindow window;
    sf::Font font;

    sf::VertexArray gridToVertexArray(AlgorithmResult result);
    sf::Color getNodeColor(Node* node, std::vector<Node> path);
};  