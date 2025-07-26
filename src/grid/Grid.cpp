#include <iostream>

#include "Grid.h"
#include "NodeType.h"

Grid::Grid(std::vector<std::string> grid)
{
    int columnIndex_ = 0;
    Position startPosition;
    Position endPosition;
    for(auto line : grid) {
        std::vector<Node> aux;
        for(int index = 0; index <line.size(); index++) {
            switch (line[index])
            {
            case 'X':
                aux.push_back(Node(0L, Position(index, columnIndex_), NodeType::WALL, false));
                break;
            case 'O':
                aux.push_back(Node(0L, Position(index, columnIndex_), NodeType::EMPTY, false));
                break;
            case 'S':
                aux.push_back(Node(0L, Position(index, columnIndex_), NodeType::START, false));
                startPosition = Position(index, columnIndex_);
                break;
            case 'E':
                aux.push_back(Node(0L, Position(index, columnIndex_), NodeType::END, false));
                endPosition = Position(index, columnIndex_);
                break;  
            default:
                break;
            }
        }
        grid_.push_back(aux);
        columnIndex_++;
    }
    startNode_ = &grid_[startPosition.y][startPosition.x];
    endNode_ = &grid_[endPosition.y][endPosition.x];
}

Grid::~Grid()
{
}

void Grid::printGrid() {
    for(int columnIndex = 0; columnIndex<grid_.size(); columnIndex++) {
        for(int rowIndex = 0; rowIndex<grid_[columnIndex].size(); rowIndex++) {
            std::cout << grid_[columnIndex][rowIndex].getChar();
        }
        std::cout << std::endl;
    }
    std::cout << "Start Position: " << startNode_->getPosition().x << " , " << startNode_->getPosition().y << std::endl;
    std::cout << "End Position: " << endNode_->getPosition().x << " , " << endNode_->getPosition().y << std::endl;
}