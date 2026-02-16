#include <iostream>
#include <string>
#include <vector>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/algorithms/DFS.hpp"
#include "Pathfinding/algorithms/Dijkstra.hpp"
#include "Pathfinding/algorithms/AStar.hpp"

int main() {
    std::cout << "Pathfinding Visualizer initialized!\n" << std::endl;

    /*std::vector<std::string> grid =
    { "XXXXXXXXXXXXXXXX"
    , "XOSOOOWOOOOOOOOX"
    , "XOXXXXXXOXXXXXOX"
    , "XOOOOXOOOOOOXOOX"
    , "XOXXOXOXXXOOXOOX"
    , "XOOGOXOOOOWOOOOX"
    , "XOXXXXXXXOXXXXXX"
    , "XOWWWWOEOOOOOOOX"
    , "XXXXXXXXXXXXXXXX"
    };*/
    /*std::vector<std::string> grid =
    { "XXXXXXXX"
    , "XOOOOOOX"
    , "XOSXOOOX"
    , "XOOXOOOX"
    , "XXXXXOXX"
    , "XOXOOOOX"
    , "XOEOXOOX"
    , "XXXXXXXX"
    };*/
    /*
    std::vector<std::string> grid =
    { "XXXXXXXX"
    , "XOOOOOOX"
    , "XOOSOOOX"
    , "XWWWWGOX"
    , "XWWWWWOX"
    , "XWWWWOOX"
    , "XOOEOOOX"
    , "XXXXXXXX"
    };
    */
   std::vector<std::string> grid =
    { "XXXXXXXXXXXXX"
    , "XOOOOOOOOOOOX"
    , "XOXOXOOSOOOOX"
    , "XOXOOXXXXXXXX"
    , "XOXOOOWWWWWOX"
    , "XOXOOOWWWWOOX"
    , "XOOOOOOOOWWWX"
    , "XOXXXXXXXWWWX"
    , "XWWOOOOOOWWWX"
    , "XEOOOOOOOWWWX"
    , "XXXXXXXXXXXXX"
    };

    Grid g(grid);
    g.printGrid();

    BFS bfs;
    DFS dfs;
    Dijkstra dijkstra;
    AStar a_star;
    
    std::cout << "----------- BFS -----------" << std::endl;
    bfs.runAlgorithm(g);

    std::cout << "----------- DFS -----------" << std::endl;
    dfs.runAlgorithm(g);
    
   std::cout << "----------- Dijkstra -----------" << std::endl;
   dijkstra.runAlgorithm(g);

   std::cout << "----------- A* -----------" << std::endl;
   a_star.runAlgorithm(g);

    return 0;
}