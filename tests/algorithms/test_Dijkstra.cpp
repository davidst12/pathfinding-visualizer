#include <gtest/gtest.h>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/algorithms/Dijkstra.hpp"
#include "utils_Grids.hpp"

TEST(DijkstraTest, TestDijkstraSimpleMap1) {
    Dijkstra dijkstra;
    Grid g("grid1", grid1);

    dijkstra.prepare(g);
    AlgorithmResult dijkstra_result = dijkstra.solve();

    EXPECT_EQ(dijkstra_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dijkstra_result.path.size(), 4);
    EXPECT_EQ(dijkstra_result.nodes_processed_count, 4);
    EXPECT_EQ(dijkstra_result.nodes_processed_ratio, 100);
}

TEST(DijkstraTest, TestDijkstraSimpleMap2) {
    Dijkstra dijkstra;
    Grid g("grid2", grid2);

    dijkstra.prepare(g);
    AlgorithmResult dijkstra_result = dijkstra.solve();

    EXPECT_EQ(dijkstra_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dijkstra_result.path.size(), 6);
    EXPECT_EQ(dijkstra_result.nodes_processed_count, 12);
    EXPECT_EQ(dijkstra_result.nodes_processed_ratio, 100);
}

TEST(DijkstraTest, TestDijkstraSimpleMap3) {
    Dijkstra dijkstra;
    Grid g("grid3", grid3);

    dijkstra.prepare(g);
    AlgorithmResult dijkstra_result = dijkstra.solve();

    EXPECT_EQ(dijkstra_result.state, AlgorithmState::PATH_NOT_FOUND);
    EXPECT_EQ(dijkstra_result.path.size(), 0);
    EXPECT_EQ(dijkstra_result.nodes_processed_count, 6);
    EXPECT_EQ(dijkstra_result.nodes_processed_ratio, 100 * 6/9);
}

TEST(DijkstraTest, TestDijkstraSimpleMap4) {
    Dijkstra dijkstra;
    Grid g("grid4", grid4);

    dijkstra.prepare(g);
    AlgorithmResult dijkstra_result = dijkstra.solve();

    EXPECT_EQ(dijkstra_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dijkstra_result.path.size(), 7);
    EXPECT_EQ(dijkstra_result.nodes_processed_count, 8);
    EXPECT_EQ(dijkstra_result.nodes_processed_ratio, 100 * 8/10);
    EXPECT_TRUE(dijkstra_result.time > std::chrono::nanoseconds(0));
}

TEST(DijkstraTest, TestDijkstraSimpleMap5) {
    Dijkstra dijkstra;
    Grid g("grid5", grid5);

    dijkstra.prepare(g);
    AlgorithmResult dijkstra_result = dijkstra.solve();

    EXPECT_EQ(dijkstra_result.state, AlgorithmState::PATH_FOUND);
    EXPECT_EQ(dijkstra_result.path.size(), 5);
    EXPECT_EQ(dijkstra_result.nodes_processed_count, 18);
    EXPECT_EQ(dijkstra_result.nodes_processed_ratio, 100 * 18/25);
    EXPECT_TRUE(dijkstra_result.time > std::chrono::nanoseconds(0));
}

TEST(DijkstraTest, TestDijkstraSimpleMap1StepMode) {
    Dijkstra dijkstra;
    Grid g("grid1", grid1);
    AlgorithmResult dijkstra_result;
    int expected_steps = 4;

    dijkstra.prepare(g);
    for(int step = 1; step <= expected_steps; step++) {
        dijkstra_result = dijkstra.step();
        EXPECT_EQ(dijkstra_result.state, step < expected_steps ? AlgorithmState::RUNNING : AlgorithmState::PATH_FOUND);
    }

    EXPECT_EQ(dijkstra_result.path.size(), 4);
    EXPECT_EQ(dijkstra_result.nodes_processed_count, 4);
    EXPECT_EQ(dijkstra_result.nodes_processed_ratio, 100);
}