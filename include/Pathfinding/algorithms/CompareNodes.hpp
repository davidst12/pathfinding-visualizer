#pragma once

#include "Pathfinding/core/Node.hpp"

class CompareNodes {
    public:
        bool operator()(Node* a, Node* b) {
            return a->getCost() > b->getCost();
        }
};