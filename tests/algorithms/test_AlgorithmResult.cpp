#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/AStar.hpp"
#include "utils_Grids.hpp"

TEST(AlgorithmResultTest, ResultRoStringTest) {
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

    EXPECT_TRUE(a_star_result.toString().contains(state_string_expected));
    EXPECT_TRUE(a_star_result.toString().contains(nodes_proc_string_expected));
    EXPECT_TRUE(a_star_result.toString().contains(nodes_ratio_string_expected));
    EXPECT_TRUE(a_star_result.toString().contains(time_string_expected));
    EXPECT_TRUE(a_star_result.toString().contains(path_size_string_expected));
    EXPECT_TRUE(a_star_result.toString().contains(cost_string_expected));
}