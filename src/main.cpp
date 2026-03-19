#include "Pathfinding/app/App.hpp"

std::unique_ptr<IVisualization> createVisualization(VisualizationType type) {
    switch (type) {
        case VisualizationType::Terminal:
            return std::make_unique<TerminalVisualization>();
        case VisualizationType::Sfml:
            return std::make_unique<SfmlVisualization>();
        default:
            throw std::runtime_error("Invalid visualization type");
    }
}

int main(int argc, char* argv[]) {

    VisualizationType mode = VisualizationType::Terminal;
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--sfml" || arg == "-s") {
            mode = VisualizationType::Sfml;
        }
    }

    std::unique_ptr<IMapManager> map_manager = std::make_unique<MapManager>();
    std::unique_ptr<IVisualization> visualization = createVisualization(mode);
    std::unique_ptr<Player> player = std::make_unique<Player>(std::move(visualization));

    App app(std::move(player), std::move(map_manager));
    app.run();

   return 0;
}