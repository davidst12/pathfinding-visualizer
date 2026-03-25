#pragma once

#include <chrono>
#include <queue>
#include <vector>

#include "Pathfinding/algorithms/IAlgorithm.hpp"

class BFS : public IAlgorithm {
   public:
    BFS();
    ~BFS() override = default;

    bool prepare(Grid& grid) override;
    AlgorithmResult solve() override;
    AlgorithmResult step() override;

   private:
    std::queue<Node*> m_nodes_to_process_queue;  ///< Cola de nodos a procesar durante el algoritmo.

    void resetAlgorithm(Grid& grid) override;

    void processNode() override;

    void checkNeightbors(Node* current_node) override;

    void algorithmStateChange(AlgorithmState state) override;

    std::vector<Node> getPath() override;

    void generateStatistics() override;
};
