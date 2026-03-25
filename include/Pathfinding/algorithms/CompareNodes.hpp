#pragma once

#include "Pathfinding/core/Node.hpp"

class CompareNodes {
   public:
    bool operator()(Node* first, Node* second) {
        return first->getCostToEnd() > second->getCostToEnd();
    }
};