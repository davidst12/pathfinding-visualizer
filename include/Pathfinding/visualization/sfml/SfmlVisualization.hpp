#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Pathfinding/algorithms/AlgorithmResult.hpp"
#include "Pathfinding/app/AppState.hpp"
#include "Pathfinding/app/AppStateEvent.hpp"
#include "Pathfinding/player/AlgorithmPreparation.hpp"
#include "Pathfinding/visualization/IVisualization.hpp"
#include "Pathfinding/visualization/ScreenResult.hpp"
#include "Pathfinding/visualization/sfml/SelectionText.hpp"

class SfmlVisualization : public IVisualization {
   public:
    SfmlVisualization();

    BasicScreenResult displayHome() override;
    TestModeSelectionResult displayTestModeSelectionScreen() override;
    AlgorithmSelectionResult displayAlgorithmSelectionScreen(
        bool allow_multiple_selection = false) override;
    MapSelectionResult displayMapSelectionScreen(std::map<std::string, Grid> maps) override;
    ExecutionSelectionResult displayExecutionSelectionScreen() override;
    BasicScreenResult displaySimulationScreen(std::vector<AlgorithmResult> results,
                                              bool wait_for_input = true) override;

   private:
    sf::RenderWindow m_window;
    sf::Font m_font;

    void displayOptionsScreen(SelectionText& options_menu_text);

    sf::VertexArray gridToVertexArray(Grid& grid, int algorithm_index, bool is_algorithm_running);
    sf::VertexArray pathToVertexArray(AlgorithmResult result, int algorithm_index);
    sf::Color getNodeColor(Node* node, bool is_algorithm_running);

    sf::Text statisticsToText(AlgorithmResult result, int algorithm_index);
};