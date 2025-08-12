#include <iostream>
#include <string>
#include <vector>

#include "grid/Grid.h"
#include "algorithms/BFS.h"

int main() {
    std::cout << "Pathfinding Visualizer initialized!\n" << std::endl;

    /*std::vector<std::string> grid =
    { "XXXXXXXX"
    , "XOOOOOOX"
    , "XOSOOOOX"
    , "XOOOOOOX"
    , "XOOOOOOX"
    , "XOOOOOOX"
    , "XOEOOOOX"
    , "XXXXXXXX"
    };*/
    std::vector<std::string> grid =
    { "XXXXXXXX"
    , "XOOOOOOX"
    , "XOSXOOOX"
    , "XOOXOOOX"
    , "XXXXXOXX"
    , "XOXOOOOX"
    , "XOEOXOOX"
    , "XXXXXXXX"
    };

    Grid g(grid);
    g.printGrid();

    BFS bfs(g);
    bfs.runAlgorithm();

    return 0;
}