#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/core/Node.hpp"
#include "Pathfinding/player/AlgorithmPreparation.hpp"

enum class AlgorithmState : std::int8_t { kIdle, kReady, kRunning, kPathFound, kPathNotFound };

inline std::string state_to_string(AlgorithmState state) {
    std::string enum_as_string;
    switch (state) {
        case AlgorithmState::kIdle:
            enum_as_string = "IDLE";
            break;
        case AlgorithmState::kReady:
            enum_as_string = "READY";
            break;
        case AlgorithmState::kRunning:
            enum_as_string = "RUNNING";
            break;
        case AlgorithmState::kPathFound:
            enum_as_string = "PATH_FOUND";
            break;
        case AlgorithmState::kPathNotFound:
            enum_as_string = "PATH_NOT_FOUND";
            break;
        default:
            break;
    }
    return enum_as_string;
}

struct AlgorithmResult {
    AlgorithmType algorithm_type = AlgorithmType::kUnknown;
    AlgorithmState state = AlgorithmState::kIdle;
    Grid* grid_resolved = nullptr;
    std::vector<Node> path;
    int nodes_processed_count = 0;
    float nodes_processed_ratio = 0;
    std::chrono::microseconds time = std::chrono::microseconds(0);

    std::string toString() const {
        std::string result_string = "Algorithm Result:\n";
        result_string += "  Algorithm: " + algorithm_type_to_string(algorithm_type) + "\n";
        result_string += "  State: " + state_to_string(state) + "\n";
        result_string += "  Nodes processed count: " + std::to_string(nodes_processed_count) +
                         " (" + std::to_string(grid_resolved->getEmptyNodesCount()) + ")\n";
        result_string +=
            "  Nodes processed ratio: " + std::to_string(nodes_processed_ratio) + "% \n";
        result_string += "  Time taken (microseconds): " + std::to_string(time.count()) + "\n";
        result_string += "  Path size: " + std::to_string(path.size()) + "\n";
        result_string +=
            "  Cost: " + std::to_string(grid_resolved->end_node->getPathWeight()) + "\n";
        return result_string;
    }
};
