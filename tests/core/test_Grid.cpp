#include <gtest/gtest.h>
#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/core/Position.hpp"

const std::vector<std::string> grid =
    { "XXXX"
    , "XSWX"
    , "XOEX"
    , "XXXX"
    };

TEST(GridTest, TestGridDimensionsAndNodeCounts) {
    Grid g(grid);

    EXPECT_EQ(g.getGridWidth(), 4);
    EXPECT_EQ(g.getGridHeight(), 4);
    EXPECT_EQ(g.getEmptyNodesCount(), 4);
    EXPECT_EQ(g.getTotalNodesCount(), 16);
}

TEST(GridTest, TestGridSpecialNodes) {
    Grid g(grid);

    Node* startNode = g.startNode_;
    Node* endNode = g.endNode_;

    EXPECT_EQ(startNode->getPosition(), Position(1, 1));
    EXPECT_EQ(endNode->getPosition(), Position(2, 2));
}

TEST(GridTest, TestGridNodesPositionValidity) {
    Grid g(grid);
    Position validPos(1, 1);
    Position invalidPos(-1, 0);

    bool validPosResult = g.checkPositionValidity(validPos);
    bool invalidPosResult = g.checkPositionValidity(invalidPos);

    EXPECT_TRUE(validPosResult);
    EXPECT_FALSE(invalidPosResult);
}

TEST(GridTest, TestGridNodesGetters) {
    Grid g(grid);
    Position waterPos(2, 1);
    Position emptyPos(1, 2);

    Node* waterNode = g.getNodeFromPosition(waterPos);
    Node* emptyNode = g.getNodeFromPosition(emptyPos);

    EXPECT_EQ(waterNode->getType(), NodeType::WATER);
    EXPECT_EQ(emptyNode->getType(), NodeType::EMPTY);
}

TEST(GridTest, TestGridToString) {
    Grid g(grid);
    std::string expectedString = "XXXX\nXSWX\nX-EX\nXXXX\n";

    std::string resultString = g.toString();

    EXPECT_EQ(resultString, expectedString);
}

TEST(GridTest, TestGridToStringWithPath) {
    Grid g(grid);
    std::vector<Node> path = { *g.getNodeFromPosition(Position(1, 1)), *g.getNodeFromPosition(Position(1, 2)), *g.getNodeFromPosition(Position(2, 2)) };
    std::string expectedString = "XXXX\nXSWX\nX+EX\nXXXX\n";

    std::string resultString = g.toStringWithPath(path);

    EXPECT_EQ(resultString, expectedString);
}