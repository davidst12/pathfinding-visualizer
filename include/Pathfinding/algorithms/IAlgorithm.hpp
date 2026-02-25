#pragma once

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/AlgorithmResult.hpp"
#include "Pathfinding/algorithms/CompareNodes.hpp"
#include <queue>

class IAlgorithm {
    public:
        IAlgorithm() {};
        virtual ~IAlgorithm() = default;
        
        virtual bool prepare(Grid& grid) = 0;
        virtual AlgorithmResult solve() = 0;
        virtual AlgorithmResult step() = 0;

    protected:
        Grid grid_;
        AlgorithmResult result_;

        Position neighbors_check_order[4] = {
            Position(0, -1),  // North
            Position(0, 1),   // South
            Position(1, 0),   // East
            Position(-1, 0),  // West
        };

        virtual void resetAlgorithm(Grid& grid) = 0;

        virtual void processNode() = 0;
        virtual void checkNeightbors(Node* current_node) = 0;

        virtual std::vector<Node> getPath() = 0;
        virtual void generateStatistics() = 0;
        virtual int heuristic(Position a, Position b) { return 0; };

        virtual void algorithmStateChange(AlgorithmState state) = 0;
};