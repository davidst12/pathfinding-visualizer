#include "Pathfinding/algorithms/AStar.hpp"

AStar::AStar(Grid& grid) : IAlgorithm(grid) {
    result_.nodes_visited_count = 1;
    result_.nodes_visited_ratio = 0;
}

void AStar::runAlgorithm() {
    grid_.startNode_->setCost(0);
    priority_node_queue_.push(grid_.startNode_);
    algorithmStateChange(AlgorithmState::RUNNING);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    while(!priority_node_queue_.empty() && result_.state == AlgorithmState::RUNNING) {
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

void AStar::processNode() {
    Node* current_node = priority_node_queue_.top();
    current_node->setVisited(true);
    current_node->setProcessed(true);
    result_.nodes_visited_count += 1;

    if(current_node->getType() == NodeType::END) {
        algorithmStateChange(AlgorithmState::PATH_FOUND);
        return;
    }
    priority_node_queue_.pop();
    checkNeightbors(current_node);
}

void AStar::checkNeightbors(Node* current_node) {
    for(int index = 0; index < 4; index++) {
        Position neightbor_position = current_node->getPosition() + neighbors_check_order[index];
        Node* neightbor_node = grid_.getNodeFromPosition(neightbor_position);

        if(neightbor_node->getType() == NodeType::WALL) continue;
        else if(neightbor_node->isVisited()) {
            int tentative_cost = current_node->getPathWeight() + neightbor_node->getWeight();
            if(tentative_cost >= neightbor_node->getPathWeight()) continue;
        }

        neightbor_node->setPathWeight(current_node->getPathWeight() + neightbor_node->getWeight());
        neightbor_node->setCost(neightbor_node->getPathWeight()
            + heuristic(neightbor_node->getPosition(), grid_.endNode_->getPosition())
        );
        neightbor_node->setParent(current_node);
        neightbor_node->setVisited(true);
        priority_node_queue_.push(neightbor_node);
    
        if(neightbor_node->getType() == NodeType::END) {
            algorithmStateChange(AlgorithmState::PATH_FOUND);
            return;
        }
    }
}

std::vector<Node> AStar::getPath() {
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

void AStar::algorithmStateChange(AlgorithmState state) {
    if(result_.state != state) {
        std::cout << "Algorithm state: " << state_to_string(state) << std::endl;
        result_.state = state;
    }
}

void AStar::generateStatistics() {
    result_.nodes_visited_ratio = 100 * result_.nodes_visited_count / grid_.getEmptyNodesCount();

    std::cout << "Algorithm statistics: \n"
        << "  Nodes visited: " << result_.nodes_visited_count << "(" <<  grid_.getEmptyNodesCount() << ")\n"
        << "  Nodes visited ratio: " << result_.nodes_visited_ratio << "%" << std::endl
        << "  Time spent (microseconds): " << result_.time.count() << std::endl
        << "  Path size: " << result_.path.size() << std::endl
        << "  Cost: " << grid_.endNode_->getCost() << std::endl;
}

int AStar::heuristic(Position a, Position b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
