#include "Pathfinding/core/Grid.hpp"

#include <iostream>

Grid::Grid(std::string name, std::vector<std::string> grid) {
    int column_index = 0;
    Position start_position;
    Position end_position;
    grid_info.name = name;
    grid_info.empty_nodes_count = 0;
    grid_info.total_nodes_count = 0;

    for (auto line : grid) {
        std::vector<Node> aux;
        for (int index = 0; index < line.size(); index++) {
            grid_info.total_nodes_count += 1;

            switch (line[index]) {
                case 'X':
                    aux.push_back(Node(Position(index, column_index), NodeType::kWall));
                    break;
                case 'O':
                    aux.push_back(Node(Position(index, column_index), NodeType::kEmpty));
                    grid_info.empty_nodes_count += 1;
                    break;
                case 'S':
                    aux.push_back(Node(Position(index, column_index), NodeType::kStart));
                    grid_info.empty_nodes_count += 1;
                    start_position = Position(index, column_index);
                    break;
                case 'E':
                    aux.push_back(Node(Position(index, column_index), NodeType::kEnd));
                    grid_info.empty_nodes_count += 1;
                    end_position = Position(index, column_index);
                    break;
                case 'R':
                    aux.push_back(Node(Position(index, column_index), NodeType::kRoad));
                    grid_info.empty_nodes_count += 1;
                    break;
                case 'G':
                    aux.push_back(Node(Position(index, column_index), NodeType::kGrass));
                    grid_info.empty_nodes_count += 1;
                    break;
                case 'W':
                    aux.push_back(Node(Position(index, column_index), NodeType::kWater));
                    grid_info.empty_nodes_count += 1;
                    break;
                default:
                    break;
            }
        }
        m_grid.push_back(aux);
        column_index++;
    }

    grid_info.height = static_cast<int>(m_grid.size());
    grid_info.width = static_cast<int>(m_grid[0].size());

    start_node = &m_grid[start_position.y][start_position.x];
    end_node = &m_grid[end_position.y][end_position.x];
}

std::string Grid::toString() const {
    std::string grid_string;

    for (int column_index = 0; column_index < m_grid.size(); column_index++) {
        for (int rowIndex = 0; rowIndex < m_grid[column_index].size(); rowIndex++) {
            grid_string += m_grid[column_index][rowIndex].getChar();
        }
        grid_string += "\n";
    }

    return grid_string;
}

std::string Grid::toStringWithPath(std::vector<Node> path) const {
    std::string grid_string;

    for (int column_index = 0; column_index < m_grid.size(); column_index++) {
        for (int rowIndex = 0; rowIndex < m_grid[column_index].size(); rowIndex++) {
            Node node = m_grid[column_index][rowIndex];
            bool found = false;
            for (int i = 0; i < path.size(); i++) {
                if (node.getPosition() == path[i].getPosition() &&
                    (path[i].getType() != NodeType::kEnd &&
                     path[i].getType() != NodeType::kStart)) {
                    grid_string += "+";
                    found = true;
                }
            }
            if (!found) {
                grid_string += m_grid[column_index][rowIndex].getChar();
            }
        }
        grid_string += "\n";
    }
    return grid_string;
}

std::string Grid::getName() const {
    return grid_info.name;
}

Node* Grid::getNodeFromPosition(Position pos) {
    return &m_grid[pos.y][pos.x];
}

int Grid::getGridHeight() const {
    return grid_info.height;
}

int Grid::getGridWidth() const {
    return grid_info.width;
}

bool Grid::checkPositionValidity(Position pos) const {
    return !((pos.x >= grid_info.width || pos.x < 0) || (pos.y >= grid_info.height || pos.y < 0));
}

int Grid::getEmptyNodesCount() const {
    return grid_info.empty_nodes_count;
}

int Grid::getTotalNodesCount() const {
    return grid_info.total_nodes_count;
}
