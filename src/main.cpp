#include "Pathfinding/app/App.hpp"

int main(int argc, char* argv[]) {

    VisualizationType mode = VisualizationType::Terminal;
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--sfml" || arg == "-s") {
            mode = VisualizationType::Sfml;
        }
    }

    App app;
    app.run(mode);

   return 0;
}