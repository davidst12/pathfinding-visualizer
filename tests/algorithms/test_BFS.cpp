#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "utils_Grids.hpp"

TEST(BFSTest, TestBfsSimpleMap1) {
    BFS bfs;
    Grid g("grid 1", grid1);

    bfs.prepare(g);
    AlgorithmResult bfs_result = bfs.solve();

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 4);
    EXPECT_EQ(bfs_result.nodes_processed_count, 4);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100);
}

TEST(BFSTest, TestBfsSimpleMap2) {
    BFS bfs;
    Grid g("grid 2", grid2);

    bfs.prepare(g);
    AlgorithmResult bfs_result = bfs.solve();

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 6);
    EXPECT_EQ(bfs_result.nodes_processed_count, 12);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100);
}

TEST(BFSTest, TestBfsSimpleMap3) {
    BFS bfs;
    Grid g("grid 3", grid3);

    bfs.prepare(g);
    AlgorithmResult bfs_result = bfs.solve();

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_NOT_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 0);
    EXPECT_EQ(bfs_result.nodes_processed_count, 6);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100 * 6/9);
}

TEST(BFSTest, TestBfsSimpleMap4) {
    BFS bfs;
    Grid g("grid 4", grid4);

    bfs.prepare(g);
    AlgorithmResult bfs_result = bfs.solve();

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 5);
    EXPECT_EQ(bfs_result.nodes_processed_count, 8);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100 * 8/10);
    EXPECT_TRUE(bfs_result.time > std::chrono::nanoseconds(0));
}

TEST(BFSTest, TestBfsSimpleMap5) {
    BFS bfs;
    Grid g("grid 5", grid5);

    bfs.prepare(g);
    AlgorithmResult bfs_result = bfs.solve();

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 5);
    EXPECT_EQ(bfs_result.nodes_processed_count, 10);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100 * 10/25);
    EXPECT_TRUE(bfs_result.time > std::chrono::nanoseconds(0));
}

TEST(BFSTest, TestBfsSimpleMap1StepMode) {
    BFS bfs;
    Grid g("grid1", grid1);
    AlgorithmResult bfs_result;
    int expected_steps = 4;

    bfs.prepare(g);
    for(int step = 1; step <= expected_steps; step++) {
        bfs_result = bfs.step();
        EXPECT_EQ(bfs_result.state, step < expected_steps ? AlgorithmState::RUNNING : AlgorithmState::PATH_FOUND);
    }

    EXPECT_EQ(bfs_result.path.size(), 4);
    EXPECT_EQ(bfs_result.nodes_processed_count, 4);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100);
}