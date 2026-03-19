#include <gtest/gtest.h>

#include <climits>

#include "Pathfinding/core/Node.hpp"
#include "Pathfinding/core/Position.hpp"

class NodeBase : public ::testing::Test {};
class NodeParamTest : public NodeBase, public ::testing::WithParamInterface<NodeType> {};
class NodeSimpleTest : public NodeBase {};


TEST(NodeSimpleTest, TestStateOperations) {
    Node node(Position(1, 1), NodeType::EMPTY);
    
    EXPECT_EQ(node.getState(), NodeState::UNDISCOVERED);
    
    node.setState(NodeState::DISCOVERED);
    EXPECT_EQ(node.getState(), NodeState::DISCOVERED);
    
    node.setState(NodeState::PROCESSED);
    EXPECT_EQ(node.getState(), NodeState::PROCESSED); 
}

TEST(NodeSimpleTest, TestPositionOperations) {
    Node node(Position(1, 1), NodeType::EMPTY);
    
    EXPECT_EQ(node.getPosition(), Position(1, 1));
    
    node.setPosition(Position(2, 2));
    EXPECT_EQ(node.getPosition(), Position(2, 2));
}

TEST(NodeSimpleTest, TestParentOperations) {
    Node node(Position(1, 1), NodeType::EMPTY);
    Node parent_node(Position(2, 2), NodeType::EMPTY);
    
    EXPECT_EQ(node.getParent(), nullptr);
    
    node.setParent(&parent_node);
    EXPECT_EQ(node.getParent(), &parent_node);
}

TEST_P(NodeParamTest, TestTypeAndWeightOperations) {
    Node node(Position(1, 1), GetParam());
    
    EXPECT_EQ(node.getType(), GetParam());
    EXPECT_EQ(node.getWeight(), weightFromNodeType(GetParam()));

    node.setType(NodeType::WALL);
    EXPECT_EQ(node.getType(), NodeType::WALL);
    EXPECT_EQ(node.getWeight(), weightFromNodeType(NodeType::WALL));
}

TEST_P(NodeParamTest, TestCharOperations) {
    Node node(Position(1, 1), GetParam());
    
    EXPECT_EQ(node.getChar(), charFromNodeType(GetParam()));
}

TEST(NodeSimpleTest, TestCostToEndOperations) {
    Node node(Position(1, 1), NodeType::EMPTY);

    EXPECT_EQ(node.getCostToEnd(), INT_MAX); 

    node.setCostToEnd(10);
    EXPECT_EQ(node.getCostToEnd(), 10);    
}

TEST(NodeSimpleTest, TestPathWeightOperations) {
    Node node(Position(1, 1), NodeType::EMPTY);

    EXPECT_EQ(node.getPathWeight(), 0); 

    node.setPathWeight(10);
    EXPECT_EQ(node.getPathWeight(), 10);    
}

TEST(NodeSimpleTest, TestNodeToString) {
    Node node(Position(1, 1), NodeType::EMPTY);
    Node parent_node(Position(2, 2), NodeType::WALL);
    node.setParent(&parent_node);
    parent_node.setState(NodeState::DISCOVERED);

    std::string expectedNodeString = "Node {1 , 1}\n  Parent {2 , 2}  State 0";
    std::string expectedParentNodeString = "Node {2 , 2}\n  Parent null  State 1";


    EXPECT_EQ(node.toString(), expectedNodeString); 
    EXPECT_EQ(parent_node.toString(), expectedParentNodeString);    
}

INSTANTIATE_TEST_SUITE_P(
    AllNodeTypes,             // Nombre único de la instancia
    NodeParamTest,             // Nombre de la clase fixture
    ::testing::Values(        // Lista de valores
        NodeType::EMPTY, 
        NodeType::WALL, 
        NodeType::START, 
        NodeType::END, 
        NodeType::ROAD, 
        NodeType::GRASS, 
        NodeType::WATER
    )
);
