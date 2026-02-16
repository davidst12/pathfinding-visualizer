#include "Pathfinding/core/Node.hpp"

#include<iostream>

Node::Node(Position position, NodeType type)
    : position_(position)
    , type_(type)
    , state_(NodeState::UNDISCOVERED)
    , parent_(nullptr)
    , cost_to_end_(INT_MAX)
    ,path_weight_(0),
    weight_(weightFromNodeType(type)) {}

NodeState Node::getState() {
    return state_;
}
void Node::setState(NodeState new_state) {
    state_ = new_state;
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
        if(state_ == NodeState::PROCESSED) return '#';
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
        << "processed " << (state_ == NodeState::PROCESSED) << std::endl;
    }else {
        std::cout << "Node (" << position_.x << " , "
        << position_.y << ") , parent (" << parent_->getPosition().x << " , "
        << parent_->getPosition().y << ") , "
        << "processed " << (state_ == NodeState::PROCESSED) << std::endl;
    }
}