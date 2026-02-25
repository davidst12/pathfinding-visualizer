#include "Pathfinding/visualization/Visualization.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

Visualization::Visualization() {
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "Pathfinding Visualizer - SFML 3");
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente" << std::endl;
    }
}

ScreenResult Visualization::displayMainMenu() {
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

ScreenResult Visualization::displayAlgorithmSelectionScreen() {
    sf::Text text(font);
    text.setString("Select Algorithm\n   1. BFS\n   2. DFS\n   3. Dijkstra\n   4. A*");
    text.setCharacterSize(24); // En píxeles
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});

    text.setPosition({400.0f, 300.0f});

    ScreenResult screen_result;

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        window.clear(sf::Color(30, 30, 30));
        window.draw(text);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch(keyPressed->code) {
                case sf::Keyboard::Key::Num1:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 1;
                    break;
                case sf::Keyboard::Key::Num2:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 2;
                    break;
                case sf::Keyboard::Key::Num3:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 3;
                    break;
                case sf::Keyboard::Key::Num4:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 4;
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
    
ScreenResult Visualization::displayMapSelectionScreen() {
    sf::Text text(font);
    text.setString("Select Map\n   1. Map 1\n   2. Map 2\n   3. Map 3\n   4. Map 4\n   5. Map 5\n   6. Map 6");
    text.setCharacterSize(24); // En píxeles
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});

    text.setPosition({400.0f, 300.0f});

    ScreenResult screen_result;

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        window.clear(sf::Color(30, 30, 30));
        window.draw(text);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Num1:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 1;
                    break;
                case sf::Keyboard::Key::Num2:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 2;
                    break;
                case sf::Keyboard::Key::Num3:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 3;
                    break;
                case sf::Keyboard::Key::Num4:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 4;    
                    break;
                case sf::Keyboard::Key::Num5:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 5;     
                    break;
                case sf::Keyboard::Key::Num6:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 6;     
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

ScreenResult Visualization::displayExecutionSelectionScreen() {
    sf::Text text(font);
    text.setString("Select Execution mode\n   1. Fast 1\n   2. Step by step 2");
    text.setCharacterSize(24); // En píxeles
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});

    text.setPosition({400.0f, 300.0f});

    ScreenResult screen_result;

    while(screen_result.state_event == AppStateEvent::Unhandled) {
        window.clear(sf::Color(30, 30, 30));
        window.draw(text);
        window.display();
    
        const std::optional event = window.waitEvent();
    
        if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Num1: 
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 1;
                    break;
                case sf::Keyboard::Key::Num2:
                    screen_result.state_event = AppStateEvent::Continue;
                    screen_result.optionSelected = 2;
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

ScreenResult Visualization::displayPlayingScreen(AlgorithmResult result) {
    std::cout << "displayPlayingScreen 222" << std::endl;
    std::cout << state_to_string(result.state) << std::endl;
    std::cout << result.path.empty() << std::endl;
    sf::VertexArray grid = gridToVertexArray(result);

    ScreenResult screen_result;

    while(true) {
        window.clear(sf::Color(30, 30, 30));
        window.draw(grid);
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
            } else if(keyPressed->code == sf::Keyboard::Key::Right) {
                std::cout << "HOLA 222" << std::endl;
                // if(result.state == AlgorithmState::RUNNING) {
                    std::cout << "HOLA 223" << std::endl;
                    screen_result.state_event = AppStateEvent::Continue;
                    break;
                // }
            }
        }
    }
    return screen_result;
}

sf::VertexArray Visualization::gridToVertexArray(AlgorithmResult result) {
    int columnas = result.grid_resolved->getGridWidth();
    int filas = result.grid_resolved->getGridHeight();
    float tamanoCelda = 30.f;

    // 1. Necesitamos 6 vértices por cada celda (2 triángulos)
    sf::VertexArray grid(sf::PrimitiveType::Triangles, columnas * filas * 6);

    // Definimos 4 colores distintos para nuestro 2x2
    sf::Color colores[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };

    // 2. Bucle para posicionar los cuadrados
    for (int x = 0; x < columnas; ++x) {
        for (int y = 0; y < filas; ++y) {            
            // Calculamos el índice donde empiezan los 6 vértices de ESTA celda
            // Cada iteración del bucle salta de 6 en 6
            int index = (x + y * columnas) * 6;

            // Coordenadas espaciales
            float left   = x * tamanoCelda + 50.f; // +50 para no pegar al borde
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
            sf::Color colorCelda = getNodeColor(result.grid_resolved->getNodeFromPosition({x, y}), result.path);
            for (int i = 0; i < 6; ++i) {
                grid[index + i].color = colorCelda;
            }
        }
    }

    return grid;
}

sf::Color Visualization::getNodeColor(Node* node, std::vector<Node> path) {
    for (auto path_node : path) {
        if (path_node.getPosition() == node->getPosition()) {
            if (node->getType() == NodeType::START || node->getType() == NodeType::END) {
                return getNodeColor(node, std::vector<Node>());
            }
            return sf::Color::Cyan;
        }
    }
    if (path.empty()) {
        if(node->getState() == NodeState::DISCOVERED) {
            return sf::Color::Cyan;
        } else if(node->getState() == NodeState::PROCESSED) {
            return sf::Color::Red;
        }
    }
    switch(node->getType()) {
        case NodeType::START: return sf::Color::Green;
        case NodeType::END: return sf::Color::Red;
        case NodeType::WALL: return sf::Color::Magenta;
        case NodeType::ROAD: return sf::Color::Yellow;
        case NodeType::WATER: return sf::Color::Blue;
        case NodeType::GRASS: return sf::Color::Green;
        case NodeType::EMPTY: return sf::Color::Transparent;
        default: return sf::Color::White;
    }
}
