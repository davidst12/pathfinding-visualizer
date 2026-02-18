#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/AStar.hpp"
#include "utils_Grids.hpp"

TEST(AStarTest, TestAStarSimpleMap1) {
    AStar a_star;
    Grid g(grid1);

    AlgorithmResult a_star_result = a_star.runAlgorithm(g);

    EXPECT_EQ(a_star_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(a_star_result.path.size(), 4);
    EXPECT_EQ(a_star_result.nodes_processed_count, 4);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100);
    EXPECT_TRUE(a_star_result.time > std::chrono::microseconds(0));
}

TEST(AStarTest, TestAStarSimpleMap2) {
    AStar a_star;
    Grid g(grid2);

    AlgorithmResult a_star_result = a_star.runAlgorithm(g);

    EXPECT_EQ(a_star_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(a_star_result.path.size(), 6);
    EXPECT_EQ(a_star_result.nodes_processed_count, 11);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 11/12);
    EXPECT_TRUE(a_star_result.time > std::chrono::microseconds(0));
}

TEST(AStarTest, TestAStarSimpleMap3) {
    AStar a_star;
    Grid g(grid3);

    AlgorithmResult a_star_result = a_star.runAlgorithm(g);

    EXPECT_EQ(a_star_result.state, AlgorithmState::PATH_NOT_FOUND);
    EXPECT_EQ(a_star_result.path.size(), 0);
    EXPECT_EQ(a_star_result.nodes_processed_count, 6);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 6/9);
    EXPECT_TRUE(a_star_result.time > std::chrono::microseconds(0));
}

TEST(AStarTest, TestAStarSimpleMap4) {
    AStar a_star;
    Grid g(grid4);

    AlgorithmResult a_star_result = a_star.runAlgorithm(g);

    EXPECT_EQ(a_star_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(a_star_result.path.size(), 7);
    EXPECT_EQ(a_star_result.nodes_processed_count, 7);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 7/10);
    EXPECT_TRUE(a_star_result.time > std::chrono::microseconds(0));
}

TEST(AStarTest, TestAStarSimpleMap5) {
    AStar a_star;
    Grid g(grid5);

    AlgorithmResult a_star_result = a_star.runAlgorithm(g);

    EXPECT_EQ(a_star_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(a_star_result.path.size(), 5);
    EXPECT_EQ(a_star_result.nodes_processed_count, 8);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 8/25);
    EXPECT_TRUE(a_star_result.time > std::chrono::microseconds(0));
}
