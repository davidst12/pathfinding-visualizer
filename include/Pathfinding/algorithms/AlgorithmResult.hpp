#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <chrono>

#include "Pathfinding/core/Node.hpp"

enum class AlgorithmState {
    IDLE,
    RUNNING,
    PATH_FOUND,
    PATH_NOT_FOUND
};

inline std::string state_to_string(AlgorithmState state)
{
   std::string enum_as_string;
   switch (state)
   {
        case AlgorithmState::IDLE:
            enum_as_string = "IDLE";
            break;
        case AlgorithmState::RUNNING:
            enum_as_string = "RUNNING";
            break;
        case AlgorithmState::PATH_FOUND:
            enum_as_string = "PATH_FOUND";
            break;
        case AlgorithmState::PATH_NOT_FOUND:
            enum_as_string = "PATH_NOT_FOUND";
            break;
        default:
            break;
   }
   return enum_as_string;
}

struct AlgorithmResult {
    AlgorithmState state = AlgorithmState::IDLE;
    Grid *grid_resolved;
    std::vector<Node> path;
    int nodes_processed_count = 0;
    float nodes_processed_ratio = 0;
    std::chrono::microseconds time;

    inline std::string toString() {
        std::string result_string = "Algorithm Result:\n";
        result_string += "  State: "                     + state_to_string(state)                + "\n";
        result_string += "  Nodes processed count: "     + std::to_string(nodes_processed_count) + " (" + std::to_string(grid_resolved->getEmptyNodesCount()) + ")\n";
        result_string += "  Nodes processed ratio: "     + std::to_string(nodes_processed_ratio) + "% \n";
        result_string += "  Time taken (microseconds): " + std::to_string(time.count())          + "\n";
        result_string += "  Path size: "                 + std::to_string(path.size())           + "\n";
        result_string += "  Cost: "                      + std::to_string(grid_resolved->endNode_->getPathWeight()) + "\n";
        return result_string;
    }
};
