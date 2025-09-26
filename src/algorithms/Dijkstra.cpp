#include<algorithms/Dijkstra.h>

Dijkstra::Dijkstra(Grid& grid)
    :grid_(grid)
{
    algorithmStateChange(AlgorithmState::IDLE);
    // El nodo inicial siempre va a ser visitado
    result_.nodes_visited_count = 1;
    result_.nodes_visited_ratio = 0;
}

void Dijkstra::runAlgorithm() {
    grid_.startNode_->setDistance(0);
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

void Dijkstra::processNode() {
    Node* current_node = priority_node_queue_.top();
    current_node->setVisited(true);
    result_.nodes_visited_count += 1;

    if(current_node->getType() == NodeType::END) {
        algorithmStateChange(AlgorithmState::PATH_FOUND);
        return;
    }
    priority_node_queue_.pop();
    checkNeightbors(current_node);
}

void Dijkstra::checkNeightbors(Node* current_node) {
    for(int index = 0; index < 4; index++) {
        Position neightbor_position = current_node->getPosition() + neighbors_check_order[index];
        Node* neightbor_node = grid_.getNodeFromPosition(neightbor_position);

        if(neightbor_node->isVisited() == false && neightbor_node->getType() != NodeType::WALL) {
            neightbor_node->setDistance(current_node->getDistance() + neightbor_node->getWeight());
            neightbor_node->setParent(current_node);
            neightbor_node->setVisited(true);
            priority_node_queue_.push(neightbor_node);
        }
    }
}

std::vector<Node> Dijkstra::getPath() {
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

void Dijkstra::algorithmStateChange(AlgorithmState state) {
    if(result_.state != state) {
        std::cout << "Algorithm state: " << state_to_string(state) << std::endl;
        result_.state = state;
    }
}

void Dijkstra::generateStatistics() {
    result_.nodes_visited_ratio = 100 * result_.nodes_visited_count / grid_.getEmptyNodesCount();

    std::cout << "Algorithm statistics: \n"
        << "  Nodes visited: " << result_.nodes_visited_count << "(" <<  grid_.getEmptyNodesCount() << ")\n"
        << "  Nodes visited ratio: " << result_.nodes_visited_ratio << "%" << std::endl
        << "  Time spent (microseconds): " << result_.time.count() << std::endl
        << "  Path size: " << result_.path.size() << std::endl
        << "  Distance: " << grid_.endNode_->getDistance() << std::endl;
}