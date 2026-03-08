#pragma once

enum class AlgorithmType
{
    AStar,
    Dijkstra,
    BFS,
    DFS,
    Unknown
};

inline std::string algorithm_type_to_string(AlgorithmType type)
{
    std::string enum_as_string;
    switch (type)
    {
        case AlgorithmType::AStar:
            enum_as_string = "A*";
            break;
        case AlgorithmType::Dijkstra:
            enum_as_string = "Dijkstra";
            break;
        case AlgorithmType::BFS:
            enum_as_string = "BFS";
            break;
        case AlgorithmType::DFS:
            enum_as_string = "DFS";
            break;
        default:
            enum_as_string = "Unknown";
            break;
    }
    return enum_as_string;
}

enum class AlgorithmExecutionMode
{
    StepByStep,
    Instant,
    Animated,
    Unknown
};

enum class AlgorithmTestMode
{
    SingleAlgorithm,
    MultipleAlgorithms,
    Unknown
};