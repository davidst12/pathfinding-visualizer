#pragma once

enum class AlgorithmType
{
    AStar,
    Dijkstra,
    BFS,
    DFS,
    Unknown,
};

enum class AlgorithmExecutionMode
{
    StepByStep,
    Instant,
};

struct AlgorithmPreparation
{
    AlgorithmType algorithmType;
    AlgorithmExecutionMode executionMode;
    int grid_index;
};