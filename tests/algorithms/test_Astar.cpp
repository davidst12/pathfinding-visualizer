#include <gtest/gtest.h>

#include "Pathfinding/algorithms/AStar.hpp"
#include "Pathfinding/core/Grid.hpp"
#include "utils_Grids.hpp"

TEST(AStarTest, TestAStarSimpleMap1) {
    AStar a_star;
    Grid g("grid1", grid1);

    a_star.prepare(g);
    AlgorithmResult a_star_result = a_star.solve();

    EXPECT_EQ(a_star_result.state, AlgorithmState::kPathFound);
    EXPECT_EQ(a_star_result.path.size(), 4);
    EXPECT_EQ(a_star_result.nodes_processed_count, 4);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100);
}

TEST(AStarTest, TestAStarSimpleMap2) {
    AStar a_star;
    Grid g("grid2", grid2);

    a_star.prepare(g);
    AlgorithmResult a_star_result = a_star.solve();

    EXPECT_EQ(a_star_result.state, AlgorithmState::kPathFound);
    EXPECT_EQ(a_star_result.path.size(), 6);
    EXPECT_EQ(a_star_result.nodes_processed_count, 10);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 10 / 12);
}

TEST(AStarTest, TestAStarSimpleMap3) {
    AStar a_star;
    Grid g("grid3", grid3);

    a_star.prepare(g);
    AlgorithmResult a_star_result = a_star.solve();

    EXPECT_EQ(a_star_result.state, AlgorithmState::kPathNotFound);
    EXPECT_EQ(a_star_result.path.size(), 0);
    EXPECT_EQ(a_star_result.nodes_processed_count, 6);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 6 / 9);
}

TEST(AStarTest, TestAStarSimpleMap4) {
    AStar a_star;
    Grid g("grid4", grid4);

    a_star.prepare(g);
    AlgorithmResult a_star_result = a_star.solve();

    EXPECT_EQ(a_star_result.state, AlgorithmState::kPathFound);
    EXPECT_EQ(a_star_result.path.size(), 7);
    EXPECT_EQ(a_star_result.nodes_processed_count, 7);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 7 / 10);
}

TEST(AStarTest, TestAStarSimpleMap5) {
    AStar a_star;
    Grid g("grid5", grid5);

    a_star.prepare(g);
    AlgorithmResult a_star_result = a_star.solve();

    EXPECT_EQ(a_star_result.state, AlgorithmState::kPathFound);
    EXPECT_EQ(a_star_result.path.size(), 5);
    EXPECT_EQ(a_star_result.nodes_processed_count, 8);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100 * 8 / 25);
    EXPECT_TRUE(a_star_result.time > std::chrono::nanoseconds(0));
}

TEST(AStarTest, TestAStarSimpleMap1StepMode) {
    AStar a_star;
    Grid g("grid1", grid1);
    AlgorithmResult a_star_result;
    int expected_steps = 4;

    a_star.prepare(g);
    for (int step = 1; step <= expected_steps; step++) {
        a_star_result = a_star.step();
        EXPECT_EQ(a_star_result.state,
                  step < expected_steps ? AlgorithmState::kRunning : AlgorithmState::kPathFound);
    }

    EXPECT_EQ(a_star_result.path.size(), 4);
    EXPECT_EQ(a_star_result.nodes_processed_count, 4);
    EXPECT_EQ(a_star_result.nodes_processed_ratio, 100);
}
