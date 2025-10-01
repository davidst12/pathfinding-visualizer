#pragma once

#include "grid/Grid.h"
#include "common/AlgorithmResult.h"
#include "common/CompareNodes.h"
#include <queue>

class IAlgorithm {
    public:
        IAlgorithm(Grid& grid) {
            grid_ = grid;
            grid_.startNode_ = grid_.getNodeFromPosition(grid_.startNode_->getPosition());
            grid_.endNode_ = grid_.getNodeFromPosition(grid_.endNode_->getPosition());
        };
        virtual void runAlgorithm() = 0;
    protected:
        Grid grid_;
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priority_node_queue_;
        AlgorithmResult result_;

        Position neighbors_check_order[4] = {
            Position(0, -1),  // North
            Position(0, 1),   // South
            Position(1, 0),   // East
            Position(-1, 0),  // West
        };

        virtual void processNode() = 0;
        virtual void checkNeightbors(Node* current_node) = 0;

        virtual std::vector<Node> getPath() = 0;
        virtual void generateStatistics() = 0;
        virtual int heuristic(Position a, Position b) { return 0; };

        virtual void algorithmStateChange(AlgorithmState state) = 0;
};