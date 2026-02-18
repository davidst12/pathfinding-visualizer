#pragma once

#include <vector>
#include <string>

#include "Pathfinding/core/Node.hpp"
#include "Pathfinding/core/Position.hpp"

struct GridInfo {
    int width_;              
    int height_;             
    int empty_nodes_count_;
    int total_nodes_count_;
};

class Grid
{
private:

    std::vector<std::vector<Node>> grid_;

public:

    Grid(std::vector<std::string> grid);
    Grid() = default;

    Node* startNode_;
    Node* endNode_;
    GridInfo grid_info_;

    std::string toString();

    std::string toStringWithPath(std::vector<Node> path);

    Node* getNodeFromPosition(Position pos);

    int getGridHeight();

    int getGridWidth();

    int getEmptyNodesCount();

    int getTotalNodesCount();

    bool checkPositionValidity(Position pos);

};