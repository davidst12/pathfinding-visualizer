#pragma once

#include <queue>
#include <vector>
#include <chrono>

#include "Pathfinding/algorithms/IAlgorithm.hpp"

class BFS : public IAlgorithm
{
public:

    BFS(Grid& grid);

    void runAlgorithm() override;

    ~BFS() override = default;
    
private:
    //Grid grid_; ///< Rejilla donde se realiza la búsqueda.
    
    std::queue<Node*> nodes_to_process_queue_; ///< Cola de nodos a procesar durante el algoritmo.
    
    //AlgorithmResult result_; ///< Resultados del algoritmo (camino encontrado, estadísticas, etc.).
    
    /*Position neighbors_check_order[4] = {
        Position(0, -1),  // North
        Position(0, 1),   // South
        Position(1, 0),   // East
        Position(-1, 0),  // West
    };*/

    void processNode() override;

    void checkNeightbors(Node* current_node) override;

    void algorithmStateChange(AlgorithmState state) override;

    std::vector<Node> getPath() override;

    void generateStatistics() override;
};
