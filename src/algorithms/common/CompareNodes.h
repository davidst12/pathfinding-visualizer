#pragma once

#include "grid/node/Node.h"

class CompareNodes {
    public:
        bool operator()(Node* a, Node* b) {
            return a->getCost() > b->getCost();
        }
};