#pragma once

#include <vector>
#include <string>

#include "Pathfinding/core/Node.hpp"
#include "Pathfinding/core/Position.hpp"

struct GridInfo {
    std::string name_;
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

    Grid(std::string name, std::vector<std::string> grid);
    Grid() = default;

    Node* startNode_;
    Node* endNode_;
    GridInfo grid_info_;

    std::string toString() const;

    std::string toStringWithPath(std::vector<Node> path) const;

    Node* getNodeFromPosition(Position pos);

    std::string getName() const;

    int getGridHeight() const;

    int getGridWidth() const;

    int getEmptyNodesCount() const;

    int getTotalNodesCount() const;

    bool checkPositionValidity(Position pos) const;

};