#include <iostream>
#include <string>
#include <vector>

#include "grid/Grid.h"

int main() {
    std::cout << "Pathfinding Visualizer initialized!" << std::endl;

    std::vector<std::string> grid =
    { "XXXXXXXX"
    , "XOOOOOOX"
    , "XOSOOOOX"
    , "XOOOOOOX"
    , "XOOOOOOX"
    , "XOOOOOOX"
    , "XOEOOOOX"
    , "XXXXXXXX"
    };

    Grid g(grid);
    g.printGrid();

    return 0;
}