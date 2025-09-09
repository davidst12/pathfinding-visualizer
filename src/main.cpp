#include <iostream>
#include <string>
#include <vector>

#include "grid/Grid.h"
#include "algorithms/BFS.h"
#include "algorithms/DFS.h"

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
    Grid g2(grid);
    g2.printGrid();

    std::cout << "----------- BFS -----------" << std::endl;

    BFS bfs(g);
    bfs.runAlgorithm();

    std::cout << "----------- DFS -----------" << std::endl;

    DFS dfs(g2);
    dfs.runAlgorithm();

    return 0;
}