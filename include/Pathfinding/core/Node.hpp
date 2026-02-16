#pragma once

#include "Pathfinding/core/Position.hpp"

enum class NodeState {
    UNDISCOVERED,
    DISCOVERED,
    PROCESSED
};

enum class NodeType {
    EMPTY,  // Nodo vacío, donde se puede caminar
    WALL,   // Nodo muro, donde no se puede caminar
    START,  // Nodo de inicio
    END,    // Nodo de fin
    ROAD,   // Nodo camino
    GRASS,  // Nodo césped, terreno con mayor coste de movimiento
    WATER   // Nodo agua, terreno con mucho mayor coste de movimiento
};

constexpr int weightFromNodeType(NodeType type) {
    switch (type) {
        case NodeType::START: return 0;
        case NodeType::END:   return 0;
        case NodeType::EMPTY: return 1;
        case NodeType::ROAD:  return 1;
        case NodeType::GRASS: return 3;
        case NodeType::WATER: return 5;
        default:              return 100;
    }
}

class Node
{
public:

    Node(Position position, NodeType type);

    // GETTERS
    NodeState getState();
    Position getPosition();
    Node* getParent();
    NodeType getType();
    char getChar();
    int getCostToEnd() { return cost_to_end_; }
    int getWeight() { return weight_; }
    int getPathWeight() { return path_weight_; }

    // SETTERS
    void setState(NodeState new_state);
    void setPosition(Position position);
    void setParent(Node* parent);
    void setType(NodeType type);
    void setCostToEnd(int cost) { cost_to_end_ = cost; }
    void setPathWeight(int path_weight) { path_weight_ = path_weight; }

    void printNodeInformation();

private:
    Position  position_;
    NodeType  type_;
    NodeState state_;
    Node*     parent_;
    int       weight_;        
    int       path_weight_;
    int       cost_to_end_;
};