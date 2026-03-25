#include "Pathfinding/visualization/sfml/SfmlVisualization.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

SfmlVisualization::SfmlVisualization() {
    m_window = sf::RenderWindow(sf::VideoMode({800, 600}), "Pathfinding Visualizer - SFML 3");
    if (!m_font.openFromFile("assets/fonts/LiberationSans-Regular.ttf")) {
        std::cerr << "No se pudo cargar la fuente" << std::endl;
    }
}

BasicScreenResult SfmlVisualization::displayHome() {
    m_window.create(sf::VideoMode({static_cast<unsigned int>(800), 600}),
                    "Pathfinding Visualizer - SFML 3");

    sf::Text text(m_font);
    sf::Text sub_text(m_font);
    text.setString("Welcome to Path Finding Visualizer !");
    sub_text.setString("<<Press Enter to continue>>");
    text.setCharacterSize(24);
    sub_text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    sub_text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    sub_text.setStyle(sf::Text::Italic);

    sf::FloatRect textRect = text.getLocalBounds();
    sf::FloatRect sub_textRect = sub_text.getLocalBounds();

    text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
    sub_text.setOrigin({sub_textRect.size.x / 2.0f, sub_textRect.size.y / 2.0f});

    text.setPosition({400.0f, 200.0f});
    sub_text.setPosition({400.0f, 300.0f});

    BasicScreenResult screen_result;

    while (true) {
        m_window.clear(sf::Color(30, 30, 30));
        m_window.draw(text);
        m_window.draw(sub_text);
        m_window.display();

        const std::optional event = m_window.waitEvent();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                screen_result.state_event = AppStateEvent::kExit;
                break;
            } else if (keyPressed->code == sf::Keyboard::Key::B) {
                screen_result.state_event = AppStateEvent::kBack;
                break;
            }
        }
    }
    return screen_result;
}

TestModeSelectionResult SfmlVisualization::displayTestModeSelectionScreen() {
    std::string title = "Select test mode";
    std::vector<std::string> options = {"1. Single Algorithm", "2. Multiple Algorithms"};
    SelectionText optionsMenuText(title, options, m_font, false);

    TestModeSelectionResult screen_result;

    while (screen_result.state_event == AppStateEvent::kUnhandled) {
        displayOptionsScreen(optionsMenuText);

        const std::optional event = m_window.waitEvent();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    optionsMenuText.moveUp();
                    break;
                case sf::Keyboard::Key::Down:
                    optionsMenuText.moveDown();
                    break;
                case sf::Keyboard::Key::Enter:
                    screen_result.state_event = AppStateEvent::kContinue;
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::kBack;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::kExit;
                    break;
                default:
                    break;
            }
        }
    }
    switch (optionsMenuText.getSelectedOption()) {
        case 1:
            screen_result.test_mode = AlgorithmTestMode::kSingleAlgorithm;
            break;
        case 2:
            screen_result.test_mode = AlgorithmTestMode::kMultipleAlgorithms;
            break;
        default:
            break;
    }

    return screen_result;
}

AlgorithmSelectionResult SfmlVisualization::displayAlgorithmSelectionScreen(
    bool allow_multiple_selection) {
    std::string title = "Select Algorithm/s";
    std::vector<std::string> options = {"1. BFS", "2. DFS", "3. Dijkstra", "4. A*"};
    SelectionText optionsMenuText(title, options, m_font, allow_multiple_selection);

    AlgorithmSelectionResult screen_result;

    while (screen_result.state_event == AppStateEvent::kUnhandled) {
        displayOptionsScreen(optionsMenuText);

        const std::optional event = m_window.waitEvent();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    optionsMenuText.moveUp();
                    break;
                case sf::Keyboard::Key::Down:
                    optionsMenuText.moveDown();
                    break;
                case sf::Keyboard::Key::Enter:
                    if (optionsMenuText.pressedEnter()) {
                        screen_result.state_event = AppStateEvent::kContinue;
                    }
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::kBack;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::kExit;
                    break;
                default:
                    break;
            }
        }
    }
    for (auto& option : optionsMenuText.getSelectedOptions()) {
        switch (option) {
            case 1:
                screen_result.algorithms_selected.emplace(AlgorithmType::kBFS);
                break;
            case 2:
                screen_result.algorithms_selected.emplace(AlgorithmType::kDFS);
                break;
            case 3:
                screen_result.algorithms_selected.emplace(AlgorithmType::kDijkstra);
                break;
            case 4:
                screen_result.algorithms_selected.emplace(AlgorithmType::kAStar);
                break;
            default:
                break;
        }
    }

    return screen_result;
}

MapSelectionResult SfmlVisualization::displayMapSelectionScreen(std::map<std::string, Grid> maps) {
    std::string title = "Select Map";
    std::vector<std::string> options;
    std::vector<Grid> grids;
    int index = 1;
    for (const auto& [name, grid] : maps) {
        options.push_back(std::to_string(index) + ". " + name);
        grids.push_back(grid);
        index++;
    }
    SelectionText optionsMenuText(title, options, m_font);

    MapSelectionResult screen_result;

    sf::VertexArray map_preview;
    sf::Transform transformacion;
    transformacion.translate({-50.f, -50.f});

    while (screen_result.state_event == AppStateEvent::kUnhandled) {
        map_preview = gridToVertexArray(grids[optionsMenuText.getSelectedOption() - 1], 0, false);

        m_window.clear(sf::Color(30, 30, 30));
        m_window.draw(map_preview, transformacion);
        m_window.draw(optionsMenuText);
        m_window.display();

        const std::optional event = m_window.waitEvent();

        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    optionsMenuText.moveUp();
                    break;
                case sf::Keyboard::Key::Down:
                    optionsMenuText.moveDown();
                    break;
                case sf::Keyboard::Key::Enter:
                    screen_result.state_event = AppStateEvent::kContinue;
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::kBack;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::kExit;
                    break;
                default:
                    break;
            }
        }
    }
    screen_result.map_name = grids[optionsMenuText.getSelectedOption() - 1].getName();

    return screen_result;
}

ExecutionSelectionResult SfmlVisualization::displayExecutionSelectionScreen() {
    std::string title = "Select Execution mode";
    std::vector<std::string> options = {"1. Fast", "2. Step by step", "3. Animated"};
    SelectionText optionsMenuText(title, options, m_font);

    ExecutionSelectionResult screen_result;

    while (screen_result.state_event == AppStateEvent::kUnhandled) {
        displayOptionsScreen(optionsMenuText);

        const std::optional event = m_window.waitEvent();

        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    optionsMenuText.moveUp();
                    break;
                case sf::Keyboard::Key::Down:
                    optionsMenuText.moveDown();
                    break;
                case sf::Keyboard::Key::Enter:
                    screen_result.state_event = AppStateEvent::kContinue;
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::kBack;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::kExit;
                    break;
                default:
                    break;
            }
        }
    }
    switch (optionsMenuText.getSelectedOption()) {
        case 1:
            screen_result.execution_mode = AlgorithmExecutionMode::kInstant;
            break;
        case 2:
            screen_result.execution_mode = AlgorithmExecutionMode::kStepByStep;
            break;
        case 3:
            screen_result.execution_mode = AlgorithmExecutionMode::kAnimated;
            break;
        default:
            break;
    }

    return screen_result;
}

BasicScreenResult SfmlVisualization::displaySimulationScreen(std::vector<AlgorithmResult> result,
                                                             bool wait_for_input) {
    float new_window_width = 0;

    std::vector<sf::VertexArray> grids;
    std::vector<sf::VertexArray> paths;
    std::vector<sf::Text> statistics;
    for (int i = 0; i < result.size(); ++i) {
        grids.push_back(gridToVertexArray(*result[i].grid_resolved, i,
                                          result[i].state == AlgorithmState::kRunning));
        paths.push_back(pathToVertexArray(result[i], i));
        statistics.push_back(statisticsToText(result[i], i));
        new_window_width += result[i].grid_resolved->getGridWidth() * 30.f + 100.f;
    }

    if (new_window_width > m_window.getView().getSize().x) {
        m_window.create(sf::VideoMode({static_cast<unsigned int>(new_window_width), 600}),
                        "Pathfinding Visualizer - SFML 3");
        // window.setSize({static_cast<unsigned int>(new_window_width), 600});
        sf::View newView(sf::FloatRect({0.f, 0.f}, {new_window_width, 600}));
        m_window.setView(newView);
    }

    BasicScreenResult screen_result;

    while (true) {
        m_window.clear(sf::Color(30, 30, 30));
        for (int i = 0; i < result.size(); ++i) {
            m_window.draw(grids[i]);
            m_window.draw(paths[i]);
            m_window.draw(statistics[i]);
        }
        m_window.display();

        std::optional<sf::Event> event;
        if (wait_for_input)
            event = m_window.waitEvent();
        else
            event = m_window.pollEvent();

        if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                screen_result.state_event = AppStateEvent::kExit;
                break;
            } else if (keyPressed->code == sf::Keyboard::Key::B) {
                screen_result.state_event = AppStateEvent::kBack;
                break;
            } else if (keyPressed->code == sf::Keyboard::Key::Right) {
                screen_result.state_event = AppStateEvent::kContinue;
                break;
            }
        }

        if (!wait_for_input) break;
    }
    return screen_result;
}

void SfmlVisualization::displayOptionsScreen(SelectionText& optionsMenuText) {
    m_window.clear(sf::Color(30, 30, 30));
    m_window.draw(optionsMenuText);
    m_window.display();
}

sf::VertexArray SfmlVisualization::gridToVertexArray(Grid& base_grid, int algorithmIndex,
                                                     bool is_algorithm_running) {
    int columnas = base_grid.getGridWidth();
    int filas = base_grid.getGridHeight();
    float tamanoCelda = 30.f;

    float horizontal_offset = algorithmIndex * (columnas * tamanoCelda + 100);

    // 1. Necesitamos 6 vértices por cada celda (2 triángulos)
    sf::VertexArray grid(sf::PrimitiveType::Triangles, columnas * filas * 6);

    // 2. Bucle para posicionar los cuadrados
    for (int x = 0; x < columnas; ++x) {
        for (int y = 0; y < filas; ++y) {
            // Calculamos el índice donde empiezan los 6 vértices de ESTA celda
            // Cada iteración del bucle salta de 6 en 6
            int index = (x + y * columnas) * 6;

            // Coordenadas espaciales
            float left = horizontal_offset + x * tamanoCelda + 50.f;  // +50 para no pegar al borde
            float right = left + tamanoCelda;
            float top = y * tamanoCelda + 50.f;
            float bottom = top + tamanoCelda;

            // Triángulo 1
            grid[index + 0].position = {left, top};
            grid[index + 1].position = {right, top};
            grid[index + 2].position = {left, bottom};

            // Triángulo 2
            grid[index + 3].position = {left, bottom};
            grid[index + 4].position = {right, top};
            grid[index + 5].position = {right, bottom};

            // 3. Asignar color (un color distinto para cada celda)
            sf::Color colorCelda =
                getNodeColor(base_grid.getNodeFromPosition({x, y}), is_algorithm_running);
            for (int i = 0; i < 6; ++i) {
                grid[index + i].color = colorCelda;
            }
        }
    }

    return grid;
}

sf::VertexArray SfmlVisualization::pathToVertexArray(AlgorithmResult result, int algorithmIndex) {
    // 6 vértices por "punto" para hacer un cuadrado con 2 triángulos
    sf::VertexArray points(sf::PrimitiveType::Triangles, result.path.size() * 6);

    float tamanoCelda = 30.f;
    float offset = 50.f;
    float horizontal_offset =
        algorithmIndex * (result.grid_resolved->getGridWidth() * tamanoCelda + 100);

    for (size_t i = 0; i < result.path.size(); ++i) {
        auto pos = result.path[i].getPosition();
        int idx = i * 6;

        // Centro de la celda
        float cx = horizontal_offset + pos.x * tamanoCelda + offset + (tamanoCelda / 2.f);
        float cy = pos.y * tamanoCelda + offset + (tamanoCelda / 2.f);

        // Radio del punto (mitad del grosor que quieras)
        float r = 20 / 2.f;

        // Definimos los 6 puntos del cuadrado centrado
        points[idx + 0].position = {cx - r, cy - r};
        points[idx + 1].position = {cx + r, cy - r};
        points[idx + 2].position = {cx - r, cy + r};

        points[idx + 3].position = {cx - r, cy + r};
        points[idx + 4].position = {cx + r, cy - r};
        points[idx + 5].position = {cx + r, cy + r};

        for (int j = 0; j < 6; ++j) points[idx + j].color = sf::Color::Yellow;
    }
    return points;
}

sf::Color SfmlVisualization::getNodeColor(Node* node, bool is_algorithm_running) {
    if (is_algorithm_running) {
        if (node->getState() == NodeState::kProcessed && node->getType() != NodeType::kStart &&
            node->getType() != NodeType::kEnd) {
            return sf::Color(216, 227, 16);
        }
    }
    switch (node->getType()) {
        case NodeType::kStart:
            return sf::Color(255, 0, 0);
        case NodeType::kEnd:
            return sf::Color(150, 0, 0);
        case NodeType::kWall:
            return sf::Color(112, 87, 82);
        case NodeType::kRoad:
            return sf::Color(237, 232, 232);
        case NodeType::kWater:
            return sf::Color(164, 236, 245);
        case NodeType::kGrass:
            return sf::Color(143, 245, 135);
        case NodeType::kEmpty:
            return sf::Color::Transparent;
        default:
            return sf::Color::White;
    }
}

sf::Text SfmlVisualization::statisticsToText(AlgorithmResult result, int algorithmIndex) {
    float horizontal_offset = algorithmIndex * (result.grid_resolved->getGridWidth() * 30.f + 100);

    sf::Text text(m_font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);

    std::string stats = "Algorithm: " + algorithm_type_to_string(result.algorithm_type) + "\n";
    stats += "Result: " + state_to_string(result.state) + "\n";
    stats += "Path length: " + std::to_string(result.path.size()) + "\n";
    stats += "Path cost: " + std::to_string(result.grid_resolved->end_node->getPathWeight()) + "\n";
    stats += "Nodes processed: " + std::to_string(result.nodes_processed_count) + "\n";
    stats += "Nodes processed ratio: " + std::to_string(result.nodes_processed_ratio) + "%\n";
    stats += "Execution time: " + std::to_string(result.time.count()) + " ms";

    text.setString(stats);
    text.setPosition({horizontal_offset + 50.f, 400.f});

    return text;
}
