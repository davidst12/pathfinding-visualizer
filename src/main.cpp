#include <iostream>
#include <string>
#include <vector>

#include "grid/Grid.h"
#include "algorithms/BFS.h"
#include "algorithms/DFS.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/AStar.h"

int main() {
    std::cout << "Pathfinding Visualizer initialized!\n" << std::endl;

    std::vector<std::string> grid =
    { "XXXXXXXXXXXXXXXX"
    , "XOSOOOWOOOOOOOOX"
    , "XOXXXXXXOXXXXXOX"
    , "XOOOOXOOOOOOXOOX"
    , "XOXXOXOXXXOOXOOX"
    , "XOOGOXOOOOWOOOOX"
    , "XOXXXXXXXOXXXXXX"
    , "XOWWWWOEOOOOOOOX"
    , "XXXXXXXXXXXXXXXX"
    };
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
    };*/

    Grid g(grid);
    g.printGrid();
    Grid g2(grid);
    Grid g3(grid);
    Grid g4(grid);
    
    std::cout << "----------- BFS -----------" << std::endl;

    BFS bfs(g);
    bfs.runAlgorithm();

    std::cout << "----------- DFS -----------" << std::endl;

    DFS dfs(g2);
    dfs.runAlgorithm();
    
   std::cout << "----------- Dijkstra -----------" << std::endl;

   Dijkstra dijkstra(g3);
   dijkstra.runAlgorithm();

   std::cout << "----------- A* -----------" << std::endl;

   AStar a_star(g4);
   a_star.runAlgorithm();


    return 0;
}