#include "Pathfinding/app/App.hpp"

std::unique_ptr<IVisualization> createVisualization(VisualizationType type) {
    switch (type) {
        case VisualizationType::kTerminal:
            return std::make_unique<TerminalVisualization>();
        case VisualizationType::kSfml:
            return std::make_unique<SfmlVisualization>();
        default:
            throw std::runtime_error("Invalid visualization type");
    }
}

int main(int argc, char* argv[]) {
    VisualizationType mode = VisualizationType::kTerminal;
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--sfml" || arg == "-s") {
            mode = VisualizationType::kSfml;
        }
    }

    std::unique_ptr<IMapManager> map_manager = std::make_unique<MapManager>();
    std::unique_ptr<IVisualization> visualization = createVisualization(mode);
    std::unique_ptr<Player> player = std::make_unique<Player>(std::move(visualization));

    App app(std::move(player), std::move(map_manager));
    app.run();

    return 0;
}