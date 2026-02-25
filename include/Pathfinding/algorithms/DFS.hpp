#pragma once

#include "Pathfinding/algorithms/IAlgorithm.hpp"

#include <stack>
#include <vector>
#include <chrono>

class DFS : public IAlgorithm
{
public:

    DFS();

    bool prepare(Grid& grid) override;
    AlgorithmResult solve() override;
    AlgorithmResult step() override;

    ~DFS() override = default;
    
private:    
    std::stack<Node*> nodes_to_process_stack_; ///< Pila de nodos a procesar durante el algoritmo.

    void resetAlgorithm(Grid& grid) override;

    void processNode() override;

    void checkNeightbors(Node* current_node) override;

    void algorithmStateChange(AlgorithmState state) override;

    std::vector<Node> getPath() override;

    void generateStatistics() override;
};
