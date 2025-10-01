#include "algorithms/IAlgorithm.h"
#include <queue>

class Dijkstra : public IAlgorithm {
    public:
        Dijkstra(Grid& grid);
        void runAlgorithm() override;
    private:
        std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priority_node_queue_;

        void processNode() override;
        void checkNeightbors(Node* current_node) override;

        std::vector<Node> getPath() override;
        void algorithmStateChange(AlgorithmState state) override;
        
        void generateStatistics() override;
};
