#pragma once

#include "Pathfinding/core/Position.hpp"

enum class NodeType {
    EMPTY,  // Nodo vacío, donde se puede caminar
    WALL,   // Nodo muro, donde no se puede caminar
    START,  // Nodo de inicio
    END,    // Nodo de fin
    ROAD,   // Nodo camino
    GRASS,  // Nodo césped, terreno con mayor coste de movimiento
    WATER   // Nodo agua, terreno con mucho mayor coste de movimiento
};

class Node
{
public:

    Node(Position position, NodeType type);

    // GETTERS
    bool isVisited();
    Position getPosition();
    Node* getParent();
    NodeType getType();
    char getChar();
    int getCost() { return cost_; }
    int getWeight() { return weight_; }
    int getPathWeight() { return path_weight_; }
    bool isProcessed() { return processed_; }

    // SETTERS
    void setVisited(bool v);
    void setPosition(Position position);
    void setParent(Node* parent);
    void setType(NodeType type);
    void setCost(int cost) { cost_ = cost; }
    void setPathWeight(int path_weight) { path_weight_ = path_weight; }
    void setProcessed(bool p) { processed_ = p; }

    void printNodeInformation();

private:
    Position position_;
    bool visited_;
    bool processed_;
    int cost_;
    int weight_;        
    int path_weight_;
    NodeType type_;
    Node* parent_;
};