#include "Node.h"

Node::Node(long id, Position position, NodeType type, bool walkable)
    : id_(id)
    , position_(position)
    , type_(type)
    , walkable_(walkable)
    , visited_(false)
    , parent_(nullptr) {}

Node::~Node() {}

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

Node& Node::getParent() {
    return *parent_;
}
void Node::setParent(Node& parent) {
    *parent_ = parent;
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
        return 'O';
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