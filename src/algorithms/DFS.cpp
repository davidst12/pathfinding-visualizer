#include "Pathfinding/algorithms/DFS.hpp"

#include "Pathfinding/player/AlgorithmPreparation.hpp"

DFS::DFS() : IAlgorithm() {}

bool DFS::prepare(Grid& grid) {
    resetAlgorithm(grid);
    algorithmStateChange(AlgorithmState::READY);

    return true;
}

AlgorithmResult DFS::solve() {

    if(result_.state != AlgorithmState::RUNNING && result_.state != AlgorithmState::READY) {
        return result_;
    }
    algorithmStateChange(AlgorithmState::RUNNING);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    while(!nodes_to_process_stack_.empty() && result_.state == AlgorithmState::RUNNING) {
        processNode();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    result_.time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if(result_.state == AlgorithmState::PATH_FOUND) {
        result_.path = getPath();
        std::cout << grid_.toStringWithPath(result_.path);
    } else {
        algorithmStateChange(AlgorithmState::PATH_NOT_FOUND);
    }
    generateStatistics();

    return result_;
}

AlgorithmResult DFS::step() {

    if(result_.state != AlgorithmState::RUNNING && result_.state != AlgorithmState::READY) {
        return result_;
    }
    algorithmStateChange(AlgorithmState::RUNNING);
    if(!nodes_to_process_stack_.empty() && result_.state == AlgorithmState::RUNNING) {
        processNode();
    }
    if(result_.state == AlgorithmState::PATH_FOUND) {
        result_.path = getPath();
    } else if(nodes_to_process_stack_.empty()) {
        algorithmStateChange(AlgorithmState::PATH_NOT_FOUND);
    }
    generateStatistics();

    return result_;
}

void DFS::resetAlgorithm(Grid& grid) {
    result_.nodes_processed_count = 0;
    result_.nodes_processed_ratio = 0;
    result_.path = std::vector<Node>();

    grid_ = grid;
    grid_.startNode_ = grid_.getNodeFromPosition(grid_.startNode_->getPosition());
    grid_.endNode_ = grid_.getNodeFromPosition(grid_.endNode_->getPosition());

    nodes_to_process_stack_ = std::stack<Node*>();
    nodes_to_process_stack_.push(grid_.startNode_);
}

void DFS::processNode() {
    Node* current_node = nodes_to_process_stack_.top();
    current_node->setState(NodeState::PROCESSED);
    result_.nodes_processed_count += 1;

    if(current_node->getType() == NodeType::END) {
        algorithmStateChange(AlgorithmState::PATH_FOUND);
        return;
    }
    nodes_to_process_stack_.pop();
    checkNeightbors(current_node);
}

void DFS::checkNeightbors(Node* current_node) {
    for(int index = 0; index < 4; index++) {
        Position neightbor_position = current_node->getPosition() + neighbors_check_order[index];
        Node* neightbor_node = grid_.getNodeFromPosition(neightbor_position);

        if(neightbor_node->getState() == NodeState::UNDISCOVERED && neightbor_node->getType() != NodeType::WALL) {
            neightbor_node->setParent(current_node);
            neightbor_node->setState(NodeState::DISCOVERED);
            nodes_to_process_stack_.push(neightbor_node);
            neightbor_node->setPathWeight(current_node->getPathWeight() + neightbor_node->getWeight());
        }
    }
}

std::vector<Node> DFS::getPath() {
    if(result_.state != AlgorithmState::PATH_FOUND) {
        return std::vector<Node>();
    }
    std::vector<Node> path;
    Node* n = grid_.endNode_;
    while (true)
    {
        path.push_back(*n);
        n = n->getParent();
        if(n == nullptr) break;
    }
    return path;
}

void DFS::algorithmStateChange(AlgorithmState state) {
    if(result_.state != state) {
        std::cout << "Algorithm state: " << state_to_string(state) << std::endl;
        result_.state = state;
    }
}

void DFS::generateStatistics() {
    result_.algorithm_type = AlgorithmType::DFS;
    result_.nodes_processed_ratio = 100 * result_.nodes_processed_count / grid_.getEmptyNodesCount();
    result_.grid_resolved = &grid_;
}
