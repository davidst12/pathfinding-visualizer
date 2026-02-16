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
    , "XOXOXOOSOOOX"
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
    
    std::cout << "----------- BFS -----------" << std::endl;

    BFS bfs(g);
    bfs.runAlgorithm();

    std::cout << "----------- DFS -----------" << std::endl;

    DFS dfs(g);
    dfs.runAlgorithm();
    
   std::cout << "----------- Dijkstra -----------" << std::endl;

   Dijkstra dijkstra(g);
   dijkstra.runAlgorithm();

   std::cout << "----------- A* -----------" << std::endl;

   AStar a_star(g);
   a_star.runAlgorithm();

    return 0;
}