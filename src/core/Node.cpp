#include "Pathfinding/core/Node.hpp"

#include<iostream>

Node::Node(Position position, NodeType type)
    : position_(position)
    , type_(type)
    , visited_(false)
    , parent_(nullptr)
    , cost_(INT_MAX) 
{
    switch (type_)
    {
    case NodeType::EMPTY:
        weight_ = 1;
        break;
    case NodeType::ROAD:
        weight_ = 1;
        break;
    case NodeType::GRASS:
        weight_ = 3;
        break;
    case NodeType::WATER:
        weight_ = 5;
        break;
    case NodeType::START:
        weight_ = 0;
        break;
    case NodeType::END:
        weight_ = 0;
        break;
    default:
        weight_ = 100;
        break;
    }
    path_weight_ = 0;
}

bool Node::isVisited() {
    return visited_;
}
void Node::setVisited(bool v) {
    visited_ = v;
}

void Node::setPosition(Position position) {
    position_ = position;
}

Position Node::getPosition() {
    return position_;
}

Node* Node::getParent() {
    return parent_;
}
void Node::setParent(Node* parent) {
    parent_ = parent;
}

void Node::setType(NodeType type) {
    type_ = type;
}
NodeType Node::getType() {
    return type_;
}

char Node::getChar() {
    switch (type_)
    {
    case NodeType::EMPTY:
        if(visited_) return '#';
        else return '-';
    case NodeType::WALL:
        return 'X';
    case NodeType::START:
        return 'S';
    case NodeType::END:
        return 'E';
    case NodeType::ROAD:
        return 'R';
    case NodeType::GRASS:
        return 'G';    
    case NodeType::WATER:
        return 'W';
    default:
        break;
    }
}

void Node::printNodeInformation() {
    if(parent_ == nullptr) {
        std::cout << "Node (" << position_.x << " , "
        << position_.y << ") , parent (null) , " 
        << "visited " << visited_ << std::endl;
    }else {
        std::cout << "Node (" << position_.x << " , "
        << position_.y << ") , parent (" << parent_->getPosition().x << " , "
        << parent_->getPosition().y << ") , "
        << "visited " << visited_ << std::endl;
    }
}