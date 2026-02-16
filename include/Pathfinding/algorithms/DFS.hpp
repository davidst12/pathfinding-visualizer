#pragma once

#include "Pathfinding/algorithms/IAlgorithm.hpp"

#include <stack>
#include <vector>
#include <chrono>

class DFS : public IAlgorithm
{
public:

    DFS(Grid& grid);

    void runAlgorithm() override;

    ~DFS() override = default;
    
private:
    //Grid grid_; ///< Referencia al grid donde se realiza la búsqueda.
    
    std::stack<Node*> nodes_to_process_stack_; ///< Pila de nodos a procesar durante el algoritmo.
    
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
