#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/BFS.hpp"
#include "utils_Grids.hpp"

TEST(BFSTest, TestBfsSimpleMap1) {
    BFS bfs;
    Grid g(grid1);

    AlgorithmResult bfs_result = bfs.runAlgorithm(g);

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 4);
    EXPECT_EQ(bfs_result.nodes_processed_count, 4);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100);
    EXPECT_TRUE(bfs_result.time > std::chrono::microseconds(0));
}

TEST(BFSTest, TestBfsSimpleMap2) {
    BFS bfs;
    Grid g(grid2);

    AlgorithmResult bfs_result = bfs.runAlgorithm(g);

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 6);
    EXPECT_EQ(bfs_result.nodes_processed_count, 12);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100);
    EXPECT_TRUE(bfs_result.time > std::chrono::microseconds(0));
}

TEST(BFSTest, TestBfsSimpleMap3) {
    BFS bfs;
    Grid g(grid3);

    AlgorithmResult bfs_result = bfs.runAlgorithm(g);

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_NOT_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 0);
    EXPECT_EQ(bfs_result.nodes_processed_count, 6);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100 * 6/9);
    EXPECT_TRUE(bfs_result.time > std::chrono::microseconds(0));
}

TEST(BFSTest, TestBfsSimpleMap4) {
    BFS bfs;
    Grid g(grid4);

    AlgorithmResult bfs_result = bfs.runAlgorithm(g);

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 5);
    EXPECT_EQ(bfs_result.nodes_processed_count, 8);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100 * 8/10);
    EXPECT_TRUE(bfs_result.time > std::chrono::microseconds(0));
}

TEST(BFSTest, TestBfsSimpleMap5) {
    BFS bfs;
    Grid g(grid5);

    AlgorithmResult bfs_result = bfs.runAlgorithm(g);

    EXPECT_EQ(bfs_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(bfs_result.path.size(), 5);
    EXPECT_EQ(bfs_result.nodes_processed_count, 10);
    EXPECT_EQ(bfs_result.nodes_processed_ratio, 100 * 10/25);
    EXPECT_TRUE(bfs_result.time > std::chrono::microseconds(0));
}