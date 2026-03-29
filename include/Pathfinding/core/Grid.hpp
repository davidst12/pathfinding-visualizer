#pragma once

#include <string>
#include <vector>

#include "Pathfinding/core/Node.hpp"
#include "Pathfinding/core/Position.hpp"

struct GridInfo {
    std::string name;
    int width = 0;
    int height = 0;
    int empty_nodes_count = 0;
    int total_nodes_count = 0;
};

class Grid {
   private:
    std::vector<std::vector<Node>> m_grid;

   public:
    Grid(std::string name, std::vector<std::string> grid);
    Grid() = default;

    Node* start_node;
    Node* end_node;
    GridInfo grid_info;

    std::string toString() const;

    std::string toStringWithPath(std::vector<Node> path) const;

    Node* getNodeFromPosition(Position pos);

    std::string getName() const;

    int getGridHeight() const;

    int getGridWidth() const;

    int getEmptyNodesCount() const;

    int getTotalNodesCount() const;

    bool checkPositionValidity(Position pos) const;

    bool operator==(const Grid& other) const {
        return grid_info.name == other.getName();
    }
};