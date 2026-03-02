#include "Pathfinding/visualization/Visualization.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Pathfinding/visualization/OptionsMenuText.hpp"


Visualization::Visualization() {
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "Pathfinding Visualizer - SFML 3");
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente" << std::endl;
    }
}

ScreenResult Visualization::displayMainMenu() {

    // sf::View newView(sf::FloatRect({0.f, 0.f}, {800, 600}));
    // window.setView(newView);
    window = sf::RenderWindow(sf::VideoMode({static_cast<unsigned int>(800), 600}), "Pathfinding Visualizer - SFML 3");

    sf::Text text(font);
    sf::Text sub_text(font);
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

    ScreenResult screen_result;

    while(true) {
        window.clear(sf::Color(30, 30, 30));
        window.draw(text);
        window.draw(sub_text);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                screen_result.state_event = AppStateEvent::Continue;
                break;
            } else if(keyPressed->code == sf::Keyboard::Key::Escape) {
                screen_result.state_event = AppStateEvent::Exit;
                break;
            } else if(keyPressed->code == sf::Keyboard::Key::B) {
                screen_result.state_event = AppStateEvent::Back;
                break;
            }
        }
    }
    return screen_result;
}

ScreenResult Visualization::displayAlgorithmTestModeSelectionScreen(std::vector<std::string> options) {
    OptionsMenuText optionsMenuText(options, font);

    int selectedOption = 1;

    ScreenResult screen_result;

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        optionsMenuText.newSelectedPiece(selectedOption);

        window.clear(sf::Color(30, 30, 30));
        window.draw(optionsMenuText);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch(keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    if (selectedOption > 1) selectedOption -= 1;
                    break;
                case sf::Keyboard::Key::Down:
                    if (selectedOption < options.size() - 1) selectedOption += 1;
                    break;
                case sf::Keyboard::Key::Enter: 
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionsSelected.emplace(selectedOption);
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::Back;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::Exit;
                    break;
                default:
                    break;
            }
        }
    }

    return screen_result;
}

ScreenResult Visualization::displayAlgorithmSelectionScreen(std::vector<std::string> options, bool allow_multiple_selection) {
    if(allow_multiple_selection) options.push_back("<<Continue>>");
    OptionsMenuText optionsMenuText(options, font);

    int selectedOption = 1;

    ScreenResult screen_result;

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        optionsMenuText.newSelectedPiece(selectedOption);
        window.clear(sf::Color(30, 30, 30));
        window.draw(optionsMenuText);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch(keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    if (selectedOption > 1) selectedOption -= 1;
                    break;
                case sf::Keyboard::Key::Down:
                    if (selectedOption < options.size() - 1) selectedOption += 1;
                    break;
                case sf::Keyboard::Key::Enter:
                    if(!allow_multiple_selection) {
                        screen_result.state_event = AppStateEvent::Continue;
                        screen_result.optionsSelected.emplace(selectedOption);
                        break;
                    }
                    if(selectedOption == options.size() - 1) {
                        if(!screen_result.optionsSelected.empty()) screen_result.state_event = AppStateEvent::Continue;
                        break;
                    } else 
                    optionsMenuText.newPeressedPiece(selectedOption);
                    if(screen_result.optionsSelected.contains(selectedOption)) {
                        screen_result.optionsSelected.erase(selectedOption);
                    } else {
                        screen_result.optionsSelected.emplace(selectedOption);
                    }
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::Back;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::Exit;
                    break;
                default:
                    break;
            }
        }
    }

    return screen_result;
}
    
ScreenResult Visualization::displayMapSelectionScreen(std::string title, std::map<std::string, Grid> maps) {
    std::vector<std::string> options = {title};
    std::vector<Grid> grids;
    int index = 1;
    for(const auto& [name, grid] : maps) {
        options.push_back(std::to_string(index) + ". " + name);
        grids.push_back(grid);
        index++;
    }
    OptionsMenuText optionsMenuText(options, font);

    int selectedOption = 1;

    ScreenResult screen_result;

    sf::VertexArray map_preview;
    sf::Transform transformacion;
    transformacion.translate({-50.f, -50.f});

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        optionsMenuText.newSelectedPiece(selectedOption);
        map_preview = gridToVertexArray(grids[selectedOption-1], 0, false);

        window.clear(sf::Color(30, 30, 30));
        window.draw(map_preview, transformacion);
        window.draw(optionsMenuText);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    if (selectedOption > 1) selectedOption -= 1;
                    break;
                case sf::Keyboard::Key::Down:
                    if (selectedOption < options.size() - 1) selectedOption += 1;
                    break;
                case sf::Keyboard::Key::Enter: 
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionsSelected.emplace(selectedOption);
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::Back;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::Exit;
                    break;
                default:
                    break;
            }
        }
    }

    return screen_result;
}

ScreenResult Visualization::displayExecutionSelectionScreen(std::vector<std::string> options) {
    OptionsMenuText optionsMenuText(options, font);

    int selectedOption = 1;

    ScreenResult screen_result;

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        optionsMenuText.newSelectedPiece(selectedOption);
        window.clear(sf::Color(30, 30, 30));
        window.draw(optionsMenuText);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    if (selectedOption > 1) selectedOption -= 1;
                    break;
                case sf::Keyboard::Key::Down:
                    if (selectedOption < options.size() - 1) selectedOption += 1;
                    break;
                case sf::Keyboard::Key::Enter: 
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionsSelected.emplace(selectedOption);
                    break;
                case sf::Keyboard::Key::B:
                    screen_result.state_event = AppStateEvent::Back;
                    break;
                case sf::Keyboard::Key::Escape:
                    screen_result.state_event = AppStateEvent::Exit;
                    break;
                default:
                    break;
            }
        }
    }

    return screen_result;
}

ScreenResult Visualization::displayPlayingScreen(std::vector<AlgorithmResult> result, bool wait_for_input) {

    float new_window_width = 0;

    std::vector<sf::VertexArray> grids;
    std::vector<sf::VertexArray> paths;
    std::vector<sf::Text> statistics;
    for(int i = 0; i < result.size(); ++i) {
        grids.push_back(gridToVertexArray(*result[i].grid_resolved, i, result[i].state == AlgorithmState::RUNNING));
        paths.push_back(pathToVertexArray(result[i], i));
        statistics.push_back(statisticsToText(result[i], i));
        new_window_width += result[i].grid_resolved->getGridWidth() * 30.f + 100.f;
    }

    if(new_window_width > window.getView().getSize().x) {
        window = sf::RenderWindow(sf::VideoMode({static_cast<unsigned int>(new_window_width), 600}), "Pathfinding Visualizer - SFML 3");
        // window.setSize({static_cast<unsigned int>(new_window_width), 600});
        sf::View newView(sf::FloatRect({0.f, 0.f}, {new_window_width, 600}));
        window.setView(newView);
    }

    ScreenResult screen_result;

    while(true) {
        window.clear(sf::Color(30, 30, 30));
        for(int i = 0; i < result.size(); ++i) {
            window.draw(grids[i]);
            window.draw(paths[i]);
            window.draw(statistics[i]);
        }
        window.display();
    
        std::optional<sf::Event> event;
        if (wait_for_input) event = window.waitEvent();
        else event = window.pollEvent();
    
        if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                screen_result.state_event = AppStateEvent::Continue;
                break;
            } else if(keyPressed->code == sf::Keyboard::Key::Escape) {
                screen_result.state_event = AppStateEvent::Exit;
                break;
            } else if(keyPressed->code == sf::Keyboard::Key::B) {
                screen_result.state_event = AppStateEvent::Back;
                break;
            } else if(keyPressed->code == sf::Keyboard::Key::Right) {
                screen_result.state_event = AppStateEvent::Continue;
                break;
            }
        }

        if (!wait_for_input) break;
    }
    return screen_result;
}

sf::VertexArray Visualization::gridToVertexArray(Grid& base_grid, int algorithmIndex, bool is_algorithm_running) {
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
            float left   = horizontal_offset + x * tamanoCelda + 50.f; // +50 para no pegar al borde
            float right  = left + tamanoCelda;
            float top    = y * tamanoCelda + 50.f;
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
            sf::Color colorCelda = getNodeColor(base_grid.getNodeFromPosition({x, y}), is_algorithm_running);
            for (int i = 0; i < 6; ++i) {
                grid[index + i].color = colorCelda;
            }
        }
    }

    return grid;
}

sf::VertexArray Visualization::pathToVertexArray(AlgorithmResult result, int algorithmIndex) {
    // 6 vértices por "punto" para hacer un cuadrado con 2 triángulos
    sf::VertexArray points(sf::PrimitiveType::Triangles, result.path.size() * 6);
    
    float tamanoCelda = 30.f;
    float offset = 50.f;
    float horizontal_offset = algorithmIndex * (result.grid_resolved->getGridWidth() * tamanoCelda + 100);

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

sf::Color Visualization::getNodeColor(Node* node, bool is_algorithm_running) {
    if (is_algorithm_running) {
        if(node->getState() == NodeState::PROCESSED && node->getType() != NodeType::START && node->getType() != NodeType::END) {
            return sf::Color(216, 227, 16);
        }
    }
    switch(node->getType()) {
        case NodeType::START: return sf::Color(255, 0, 0);
        case NodeType::END: return sf::Color(150, 0, 0);
        case NodeType::WALL: return sf::Color(112, 87, 82);
        case NodeType::ROAD: return sf::Color(237, 232, 232);
        case NodeType::WATER: return sf::Color(164, 236, 245);
        case NodeType::GRASS: return sf::Color(143, 245, 135);
        case NodeType::EMPTY: return sf::Color::Transparent;
        default: return sf::Color::White;
    }
}

sf::Text Visualization::statisticsToText(AlgorithmResult result, int algorithmIndex) {
    float horizontal_offset = algorithmIndex * (result.grid_resolved->getGridWidth() * 30.f + 100);

    sf::Text text(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);


    std::string stats = "Algorithm: " + algorithm_type_to_string(result.algorithm_type) + "\n";
    stats += "Result: " + state_to_string(result.state) + "\n";
    stats += "Path length: " + std::to_string(result.path.size()) + "\n";
    stats += "Path cost: " + std::to_string(result.grid_resolved->endNode_->getPathWeight()) + "\n";
    stats += "Nodes processed: " + std::to_string(result.nodes_processed_count) + "\n";
    stats += "Nodes processed ratio: " + std::to_string(result.nodes_processed_ratio) + "%\n";
    stats += "Execution time: " + std::to_string(result.time.count()) + " ms";

    text.setString(stats);
    text.setPosition({horizontal_offset + 50.f, 400.f});

    return text;
}
