#pragma once

enum class AlgorithmType : std::uint8_t { kAStar, kDijkstra, kBFS, kDFS, kUnknown };

inline std::string algorithm_type_to_string(AlgorithmType type) {
    std::string enum_as_string;
    switch (type) {
        case AlgorithmType::kAStar:
            enum_as_string = "A*";
            break;
        case AlgorithmType::kDijkstra:
            enum_as_string = "Dijkstra";
            break;
        case AlgorithmType::kBFS:
            enum_as_string = "BFS";
            break;
        case AlgorithmType::kDFS:
            enum_as_string = "DFS";
            break;
        default:
            enum_as_string = "Unknown";
            break;
    }
    return enum_as_string;
}

enum class AlgorithmExecutionMode : std::uint8_t { kStepByStep, kInstant, kAnimated, kUnknown };

enum class AlgorithmTestMode : std::uint8_t { kSingleAlgorithm, kMultipleAlgorithms, kUnknown };
