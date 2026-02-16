#include "Pathfinding/algorithms/BFS.hpp"

BFS::BFS() : IAlgorithm() {}

void BFS::runAlgorithm(Grid& grid) {

    resetAlgorithm(grid);

    nodes_to_process_queue_.push(grid_.startNode_);
    algorithmStateChange(AlgorithmState::RUNNING);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    while(!nodes_to_process_queue_.empty() && result_.state == AlgorithmState::RUNNING) {
        processNode();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    result_.time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if(result_.state == AlgorithmState::PATH_FOUND) {
        result_.path = getPath();
        grid_.printGridAndPath(result_.path);
    } else {
        algorithmStateChange(AlgorithmState::PATH_NOT_FOUND);
    }
    generateStatistics();
}

void BFS::resetAlgorithm(Grid& grid) {
    result_.nodes_processed_count = 1;
    result_.nodes_processed_ratio = 0;

    grid_ = grid;
    grid_.startNode_ = grid_.getNodeFromPosition(grid_.startNode_->getPosition());
    grid_.endNode_ = grid_.getNodeFromPosition(grid_.endNode_->getPosition());

    nodes_to_process_queue_ = std::queue<Node*>();
}

void BFS::processNode() {
    Node* current_node = nodes_to_process_queue_.front();
    current_node->setState(NodeState::PROCESSED);
    result_.nodes_processed_count += 1;

    if(current_node->getType() == NodeType::END) {
        algorithmStateChange(AlgorithmState::PATH_FOUND);
        return;
    }
    nodes_to_process_queue_.pop();
    checkNeightbors(current_node);
}

void BFS::checkNeightbors(Node* current_node) {
    for(int index = 0; index < 4; index++) {
        Position neightbor_position = current_node->getPosition() + neighbors_check_order[index];
        Node* neightbor_node = grid_.getNodeFromPosition(neightbor_position);

        if(neightbor_node->getState() == NodeState::UNDISCOVERED && neightbor_node->getType() != NodeType::WALL) {
            neightbor_node->setParent(current_node);
            neightbor_node->setState(NodeState::DISCOVERED);
            nodes_to_process_queue_.push(neightbor_node);
            neightbor_node->setPathWeight(current_node->getPathWeight() + neightbor_node->getWeight());
        }
    }
}

std::vector<Node> BFS::getPath() {
    std::vector<Node> path;
    Node* n = grid_.endNode_;
    while (true)
    {
        if(n->getParent() != nullptr) {
            path.push_back(*n);
            n = n->getParent();
        } else {
            break;
        }
    }
    return path;
}

void BFS::algorithmStateChange(AlgorithmState state) {
    if(result_.state != state) {
        std::cout << "Algorithm state: " << state_to_string(state) << std::endl;
        result_.state = state;
    }
}

void BFS::generateStatistics() {
    result_.nodes_processed_ratio = 100 * result_.nodes_processed_count / grid_.getEmptyNodesCount();

    std::cout << "Algorithm statistics: \n"
        << "  Nodes visited: " << result_.nodes_processed_count << "(" <<  grid_.getEmptyNodesCount() << ")\n"
        << "  Nodes visited ratio: " << result_.nodes_processed_ratio << "%" << std::endl
        << "  Time spent (microseconds): " << result_.time.count() << std::endl
        << "  Path size: " << result_.path.size() << std::endl
        << "  Cost: " << grid_.endNode_->getPathWeight() << std::endl;
}
