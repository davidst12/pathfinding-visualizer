#pragma once

#include <cstdint>

#include "Pathfinding/core/Position.hpp"

enum class NodeState : std::uint8_t { kUndiscovered, kDiscovered, kProcessed };

enum class NodeType : std::uint8_t {
    kEmpty,  // Nodo vacío, donde se puede caminar
    kWall,   // Nodo muro, donde no se puede caminar
    kStart,  // Nodo de inicio
    kEnd,    // Nodo de fin
    kRoad,   // Nodo camino
    kGrass,  // Nodo césped, terreno con mayor coste de movimiento
    kWater   // Nodo agua, terreno con mucho mayor coste de movimiento
};

constexpr int weightFromNodeType(NodeType type) {
    switch (type) {
        case NodeType::kStart:
        case NodeType::kEnd:
            return 0;
        case NodeType::kEmpty:
        case NodeType::kRoad:
            return 1;
        case NodeType::kGrass:
            return 3;
        case NodeType::kWater:
            return 5;
        case NodeType::kWall:
        default:
            return 100;
    }
}

constexpr char charFromNodeType(NodeType type) {
    switch (type) {
        case NodeType::kStart:
            return 'S';
        case NodeType::kEnd:
            return 'E';
        case NodeType::kEmpty:
            return '-';
        case NodeType::kRoad:
            return 'R';
        case NodeType::kGrass:
            return 'G';
        case NodeType::kWater:
            return 'W';
        case NodeType::kWall:
            return 'X';
        default:
            return '-';
    }
}

class Node {
   public:
    Node(Position position, NodeType type);

    // GETTERS
    NodeState getState() const;
    Position getPosition() const;
    Node* getParent() const;
    NodeType getType() const;
    char getChar() const;
    int getCostToEnd() const {
        return m_cost_to_end;
    }
    int getWeight() const {
        return m_weight;
    }
    int getPathWeight() const {
        return m_path_weight;
    }

    // SETTERS
    void setState(NodeState new_state);
    void setPosition(Position position);
    void setParent(Node* parent);
    void setType(NodeType type);
    void setCostToEnd(int cost) {
        m_cost_to_end = cost;
    }
    void setPathWeight(int path_weight) {
        m_path_weight = path_weight;
    }

    std::string toString();

   private:
    Position m_position;
    NodeType m_type;
    NodeState m_state;
    Node* m_parent;
    int m_weight;
    int m_path_weight;
    int m_cost_to_end;
};