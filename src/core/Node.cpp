#include "Pathfinding/core/Node.hpp"

#include<iostream>

Node::Node(Position position, NodeType type)
    : position_(position)
    , type_(type)
    , state_(NodeState::UNDISCOVERED)
    , parent_(nullptr)
    , cost_to_end_(INT_MAX)
    , path_weight_(0)
    , weight_(weightFromNodeType(type)) {}

NodeState Node::getState() const {
    return state_;
}
void Node::setState(NodeState new_state) {
    state_ = new_state;
}

void Node::setPosition(Position position) {
    position_ = position;
}

Position Node::getPosition() const {
    return position_;
}

Node* Node::getParent() const {
    return parent_;
}
void Node::setParent(Node* parent) {
    parent_ = parent;
}

void Node::setType(NodeType type) {
    type_ = type;
    weight_ = weightFromNodeType(type);
}
NodeType Node::getType() const {
    return type_;
}

char Node::getChar() const {
    return charFromNodeType(type_);
}

std::string Node::toString() {
    std::string node_string = "";
    node_string += "Node " + position_.to_string() + "\n";
    node_string += "  Parent " + (parent_ != nullptr ? parent_->getPosition().to_string() : "null");
    node_string += "  State " + std::to_string(static_cast<int>(state_));

    return node_string;
}
