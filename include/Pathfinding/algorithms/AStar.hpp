#include "Pathfinding/algorithms/IAlgorithm.hpp"
#include <queue>

class AStar : public IAlgorithm {
    public:
        AStar();
        void runAlgorithm(Grid& grid) override;
    private:
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priority_node_queue_;

        void resetAlgorithm(Grid& grid) override;

        void processNode() override;
        void checkNeightbors(Node* current_node) override;

        std::vector<Node> getPath() override;
        void generateStatistics() override;
        int heuristic(Position a, Position b) override;

        void algorithmStateChange(AlgorithmState state) override;
};