#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/DFS.hpp"
#include "utils_Grids.hpp"

TEST(DFSTest, TestDfsSimpleMap1) {
    DFS dfs;
    Grid g("grid1", grid1);

    dfs.prepare(g);
    AlgorithmResult dfs_result = dfs.solve();

    EXPECT_EQ(dfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dfs_result.path.size(), 4);
    EXPECT_EQ(dfs_result.nodes_processed_count, 4);
    EXPECT_EQ(dfs_result.nodes_processed_ratio, 100);
}

TEST(DFSTest, TestDfsSimpleMap2) {
    DFS dfs;
    Grid g("grid2", grid2);

    dfs.prepare(g);
    AlgorithmResult dfs_result = dfs.solve();

    EXPECT_EQ(dfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dfs_result.path.size(), 6);
    EXPECT_EQ(dfs_result.nodes_processed_count, 10);
    EXPECT_EQ(dfs_result.nodes_processed_ratio, 100 * 10/12);
}

TEST(DFSTest, TestDfsSimpleMap3) {
    DFS dfs;
    Grid g("grid3", grid3);

    dfs.prepare(g);
    AlgorithmResult dfs_result = dfs.solve();

    EXPECT_EQ(dfs_result.state, AlgorithmState::PATH_NOT_FOUND);
    EXPECT_EQ(dfs_result.path.size(), 0);
    EXPECT_EQ(dfs_result.nodes_processed_count, 6);
    EXPECT_EQ(dfs_result.nodes_processed_ratio, 100 * 6/9);
}

TEST(DFSTest, TestDfsSimpleMap4) {
    DFS dfs;
    Grid g("grid4", grid4);

    dfs.prepare(g);
    AlgorithmResult dfs_result = dfs.solve();

    EXPECT_EQ(dfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dfs_result.path.size(), 7);
    EXPECT_EQ(dfs_result.nodes_processed_count, 7);
    EXPECT_EQ(dfs_result.nodes_processed_ratio, 100 * 7/10);
    EXPECT_TRUE(dfs_result.time > std::chrono::nanoseconds(0));
}

TEST(DFSTest, TestDfsSimpleMap5) {
    DFS dfs;
    Grid g("grid5", grid5);

    dfs.prepare(g);
    AlgorithmResult dfs_result = dfs.solve();

    EXPECT_EQ(dfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dfs_result.path.size(), 13);
    EXPECT_EQ(dfs_result.nodes_processed_count, 13);
    EXPECT_EQ(dfs_result.nodes_processed_ratio, 100 * 13/25);
    EXPECT_TRUE(dfs_result.time > std::chrono::nanoseconds(0));
}

TEST(DFSTest, TestDfsSimpleMap1StepMode) {
    DFS dfs;
    Grid g("grid1", grid1);
    AlgorithmResult dfs_result;
    int expected_steps = 4;

    dfs.prepare(g);
    for(int step = 1; step <= expected_steps; step++) {
        dfs_result = dfs.step();
        EXPECT_EQ(dfs_result.state, step < expected_steps ? AlgorithmState::RUNNING : AlgorithmState::PATH_FOUND);
    }

    EXPECT_EQ(dfs_result.path.size(), 4);
    EXPECT_EQ(dfs_result.nodes_processed_count, 4);
    EXPECT_EQ(dfs_result.nodes_processed_ratio, 100);
}