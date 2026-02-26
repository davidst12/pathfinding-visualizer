#include <iostream>
#include <string>
#include <vector>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "Pathfinding/algorithms/DFS.hpp"
#include "Pathfinding/algorithms/Dijkstra.hpp"
#include "Pathfinding/algorithms/AStar.hpp"
#include "Pathfinding/visualization/Visualization.hpp"

#include "Pathfinding/app/App.hpp"

int main() {
    std::cout << "Pathfinding Visualizer initialized!\n" << std::endl;

    App app;
    app.run();

    /*

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
    std::cout << g.toString() << std::endl;

    BFS bfs;
    DFS dfs;
    Dijkstra dijkstra;
    AStar a_star;
    
    std::cout << "----------- BFS -----------" << std::endl;
    AlgorithmResult bfs_result = bfs.runAlgorithm(g);
    std::cout << bfs_result.toString() << std::endl;

    std::cout << "----------- DFS -----------" << std::endl;
    AlgorithmResult dfs_result = dfs.runAlgorithm(g);
    std::cout << dfs_result.toString() << std::endl;
    
   std::cout << "----------- Dijkstra -----------" << std::endl;
   AlgorithmResult dijkstra_result = dijkstra.runAlgorithm(g);
    std::cout << dijkstra_result.toString() << std::endl;

   std::cout << "----------- A* -----------" << std::endl;
   AlgorithmResult a_star_result = a_star.runAlgorithm(g);
   std::cout << a_star_result.toString() << std::endl;

   */

   return 0;
}