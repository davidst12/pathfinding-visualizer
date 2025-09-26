#include "grid/Grid.h"
#include "common/AlgorithmResult.h"
#include <queue>

class CompareNodes {
    public:
        bool operator()(Node* a, Node* b) {
            return a->getDistance() > b->getDistance();
        }
};

class Dijkstra {
    public:
        Dijkstra(Grid& grid);
        void runAlgorithm();
    private:
        Grid& grid_;
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priority_node_queue_;
        AlgorithmResult result_;

        Position neighbors_check_order[4] = {
            Position(0, -1),  // North
            Position(0, 1),   // South
            Position(1, 0),   // East
            Position(-1, 0),  // West
        };

        void processNode();
        void checkNeightbors(Node* current_node);
        std::vector<Node> getPath();
        void algorithmStateChange(AlgorithmState state);
        void generateStatistics();
};
