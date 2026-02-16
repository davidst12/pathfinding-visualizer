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

struct AlgorithmResult {
    AlgorithmState state = AlgorithmState::IDLE;
    std::vector<Node> path;
    int nodes_visited_count = 0;
    float nodes_visited_ratio = 0;
    std::chrono::microseconds time;
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
