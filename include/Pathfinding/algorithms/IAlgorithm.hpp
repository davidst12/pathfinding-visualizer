#pragma once

#include <array>
#include <queue>

#include "Pathfinding/algorithms/AlgorithmResult.hpp"
#include "Pathfinding/algorithms/CompareNodes.hpp"
#include "Pathfinding/core/Grid.hpp"

class IAlgorithm {
   public:
    IAlgorithm() {};
    virtual ~IAlgorithm() = default;

    virtual bool prepare(Grid& grid) = 0;
    virtual AlgorithmResult solve() = 0;
    virtual AlgorithmResult step() = 0;

   protected:
    Grid m_grid;
    AlgorithmResult m_result;

    std::array<Position, 4> m_neighbors_check_order = {{
        Position(0, -1),  // North
        Position(0, 1),   // South
        Position(1, 0),   // East
        Position(-1, 0)   // West
    }};

    virtual void resetAlgorithm(Grid& grid) = 0;

    virtual void processNode() = 0;
    virtual void checkNeightbors(Node* current_node) = 0;

    virtual std::vector<Node> getPath() = 0;
    virtual void generateStatistics() = 0;
    virtual int heuristic(Position fisrt, Position second) {
        return 0;
    };

    virtual void algorithmStateChange(AlgorithmState state) = 0;
};