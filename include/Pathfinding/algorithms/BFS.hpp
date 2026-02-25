#pragma once

#include <queue>
#include <vector>
#include <chrono>

#include "Pathfinding/algorithms/IAlgorithm.hpp"

class BFS : public IAlgorithm
{
public:

    BFS();

    AlgorithmResult runAlgorithm(Grid& grid) override;
    AlgorithmResult runStepAlgorithm() override;
    void setGrid(Grid& grid) override;

    ~BFS() override = default;
    
private:
    std::queue<Node*> nodes_to_process_queue_; ///< Cola de nodos a procesar durante el algoritmo.

    void resetAlgorithm(Grid& grid) override;

    void processNode() override;

    void checkNeightbors(Node* current_node) override;

    void algorithmStateChange(AlgorithmState state) override;

    std::vector<Node> getPath() override;

    void generateStatistics() override;
};
