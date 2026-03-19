#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/AStar.hpp"
#include "utils_Grids.hpp"

TEST(AlgorithmResultTest, ResultToStringTest) {
    AStar a_star;
    Grid g("grid1", grid1);
    
    std::string algorithm_string_expected = "Algorithm: A*\n";
    std::string state_string_expected = "State: PATH_FOUND\n";
    std::string nodes_proc_string_expected = "Nodes processed count: 4 (4)\n";
    std::string nodes_ratio_string_expected = "Nodes processed ratio: 100.000000% \n";
    std::string time_string_expected = "Time taken (microseconds): ";
    std::string path_size_string_expected = "Path size: 4\n";
    std::string cost_string_expected = "Cost: 2\n";
    
    a_star.prepare(g);
    AlgorithmResult a_star_result = a_star.solve();

    EXPECT_TRUE(a_star_result.toString().find(state_string_expected) != std::string::npos);
    EXPECT_TRUE(a_star_result.toString().find(nodes_proc_string_expected) != std::string::npos);
    EXPECT_TRUE(a_star_result.toString().find(nodes_ratio_string_expected) != std::string::npos);
    EXPECT_TRUE(a_star_result.toString().find(time_string_expected) != std::string::npos);
    EXPECT_TRUE(a_star_result.toString().find(path_size_string_expected) != std::string::npos);
    EXPECT_TRUE(a_star_result.toString().find(cost_string_expected) != std::string::npos);
}

TEST(AlgorithmResultTest, ToStringTest) {
    EXPECT_EQ("IDLE", state_to_string(AlgorithmState::IDLE));
    EXPECT_EQ("READY", state_to_string(AlgorithmState::READY));
    EXPECT_EQ("RUNNING", state_to_string(AlgorithmState::RUNNING));
    EXPECT_EQ("PATH_FOUND", state_to_string(AlgorithmState::PATH_FOUND));
    EXPECT_EQ("PATH_NOT_FOUND", state_to_string(AlgorithmState::PATH_NOT_FOUND));

    EXPECT_EQ("Dijkstra", algorithm_type_to_string(AlgorithmType::Dijkstra));
    EXPECT_EQ("BFS", algorithm_type_to_string(AlgorithmType::BFS));
    EXPECT_EQ("DFS", algorithm_type_to_string(AlgorithmType::DFS));
    EXPECT_EQ("A*", algorithm_type_to_string(AlgorithmType::AStar));
}