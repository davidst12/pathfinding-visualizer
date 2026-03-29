#include <queue>

#include "Pathfinding/algorithms/IAlgorithm.hpp"

class AStar : public IAlgorithm {
   public:
    AStar();

    bool prepare(Grid& grid) override;
    AlgorithmResult solve() override;
    AlgorithmResult step() override;

   private:
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> m_priority_node_queue;

    void resetAlgorithm(Grid& grid) override;

    void processNode() override;
    void checkNeightbors(Node* current_node) override;

    std::vector<Node> getPath() override;
    void generateStatistics() override;
    int heuristic(Position first, Position second) override;

    void algorithmStateChange(AlgorithmState state) override;
};