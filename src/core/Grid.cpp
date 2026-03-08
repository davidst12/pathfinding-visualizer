#include <iostream>

#include "Pathfinding/core/Grid.hpp"

Grid::Grid(std::string name, std::vector<std::string> grid)
{
    int columnIndex_ = 0;
    Position startPosition;
    Position endPosition;
    grid_info_.name_ = name;
    grid_info_.empty_nodes_count_ = 0;
    grid_info_.total_nodes_count_ = 0;

    for(auto line : grid) {
        std::vector<Node> aux;
        for(int index = 0; index <line.size(); index++) {

            grid_info_.total_nodes_count_ += 1;

            switch (line[index])
            {
            case 'X':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::WALL));
                break;
            case 'O':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::EMPTY));
                grid_info_.empty_nodes_count_ += 1;
                break;
            case 'S':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::START));
                grid_info_.empty_nodes_count_ += 1;
                startPosition = Position(index, columnIndex_);
                break;
            case 'E':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::END));
                grid_info_.empty_nodes_count_ += 1;
                endPosition = Position(index, columnIndex_);
                break;
            case 'R':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::ROAD));
                grid_info_.empty_nodes_count_ += 1;
                break;
            case 'G':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::GRASS));
                grid_info_.empty_nodes_count_ += 1;
                break;
            case 'W':
                aux.push_back(Node(Position(index, columnIndex_), NodeType::WATER));
                grid_info_.empty_nodes_count_ += 1;
                break;
            default:
                break;
            }
        }
        grid_.push_back(aux);
        columnIndex_++;
    }

    grid_info_.height_ = grid_.size();
    grid_info_.width_ = grid_[0].size();

    startNode_ = &grid_[startPosition.y][startPosition.x];
    endNode_ = &grid_[endPosition.y][endPosition.x];
}

std::string Grid::toString() {
    std::string grid_string = "";

    for(int columnIndex = 0; columnIndex<grid_.size(); columnIndex++) {
        for(int rowIndex = 0; rowIndex<grid_[columnIndex].size(); rowIndex++) {
            grid_string += grid_[columnIndex][rowIndex].getChar();
        }
        grid_string += "\n";
    }

    return grid_string;
}

std::string Grid::toStringWithPath(std::vector<Node> path) {
    std::string grid_string = "";

    for(int columnIndex = 0; columnIndex<grid_.size(); columnIndex++) {
        for(int rowIndex = 0; rowIndex<grid_[columnIndex].size(); rowIndex++) {
            Node n = grid_[columnIndex][rowIndex];
            bool found = false;
            for(int i=0; i<path.size(); i++) {
                if(n.getPosition() == path[i].getPosition() && (path[i].getType() != NodeType::END && path[i].getType() != NodeType::START)) {
                    grid_string += "+";
                    found = true;
                }
            }
            if(found == false) {
                grid_string += grid_[columnIndex][rowIndex].getChar();
            }
        }
        grid_string += "\n";
    }
    return grid_string;
}

std::string Grid::getName() {
    return grid_info_.name_;
}

Node* Grid::getNodeFromPosition(Position pos) {
    return &grid_[pos.y][pos.x];
}

int Grid::getGridHeight() {
    return grid_info_.height_;
}

int Grid::getGridWidth() {
    return grid_info_.width_;
}

bool Grid::checkPositionValidity(Position pos) {
    if(pos.x >= grid_info_.width_ || pos.x < 0) return false;
    else if(pos.y >= grid_info_.height_ || pos.y < 0) return false;
    
    return true;
}

int Grid::getEmptyNodesCount() {
    return grid_info_.empty_nodes_count_;
}

int Grid::getTotalNodesCount() {
    return grid_info_.total_nodes_count_;
}
