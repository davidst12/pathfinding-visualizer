#include <iostream>

#include "Grid.h"
#include "node/NodeType.h"

Grid::Grid(std::vector<std::string> grid)
{
    int columnIndex_ = 0;
    Position startPosition;
    Position endPosition;
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

void Grid::printGrid() {
    std::cout << std::endl;
    for(int columnIndex = 0; columnIndex<grid_.size(); columnIndex++) {
        for(int rowIndex = 0; rowIndex<grid_[columnIndex].size(); rowIndex++) {
            std::cout << grid_[columnIndex][rowIndex].getChar();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grid::printGridAndPath(std::vector<Node> path) {
    std::cout << std::endl;
    for(int columnIndex = 0; columnIndex<grid_.size(); columnIndex++) {
        for(int rowIndex = 0; rowIndex<grid_[columnIndex].size(); rowIndex++) {
            Node n = grid_[columnIndex][rowIndex];
            bool found = false;
            for(int i=0; i<path.size(); i++) {
                if(n.getPosition() == path[i].getPosition() && path[i].getType() == NodeType::EMPTY) {
                    std::cout << "*";
                    found = true;
                }
            }
            if(found == false) {
                std::cout << grid_[columnIndex][rowIndex].getChar();
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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