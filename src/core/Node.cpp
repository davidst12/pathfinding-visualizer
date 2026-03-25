#include "Pathfinding/core/Node.hpp"

#include <climits>
#include <iostream>

Node::Node(Position position, NodeType type)
    : m_position(position),
      m_type(type),
      m_state(NodeState::kUndiscovered),
      m_parent(nullptr),
      m_cost_to_end(INT_MAX),
      m_path_weight(0),
      m_weight(weightFromNodeType(type)) {}

NodeState Node::getState() const {
    return m_state;
}
void Node::setState(NodeState new_state) {
    m_state = new_state;
}

void Node::setPosition(Position position) {
    m_position = position;
}

Position Node::getPosition() const {
    return m_position;
}

Node* Node::getParent() const {
    return m_parent;
}
void Node::setParent(Node* parent) {
    m_parent = parent;
}

void Node::setType(NodeType type) {
    m_type = type;
    m_weight = weightFromNodeType(type);
}
NodeType Node::getType() const {
    return m_type;
}

char Node::getChar() const {
    return charFromNodeType(m_type);
}

std::string Node::toString() {
    std::string node_string;
    node_string += "Node " + m_position.to_string() + "\n";
    node_string +=
        "  Parent " + (m_parent != nullptr ? m_parent->getPosition().to_string() : "null");
    node_string += "  State " + std::to_string(static_cast<int>(m_state));

    return node_string;
}
