#include "Node.h"

#include<iostream>

Node::Node(Position position, NodeType type)
    : position_(position)
    , type_(type)
    , visited_(false)
    , parent_(nullptr) {}

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
        if(visited_) return 'v';
        else return '-';
    case NodeType::WALL:
        return 'X';
    case NodeType::START:
        return 'S';
    case NodeType::END:
        return 'E';
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