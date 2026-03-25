#include "Pathfinding/algorithms/DFS.hpp"

#include "Pathfinding/player/AlgorithmPreparation.hpp"

DFS::DFS() {}

bool DFS::prepare(Grid& grid) {
    resetAlgorithm(grid);
    algorithmStateChange(AlgorithmState::kReady);

    return true;
}

AlgorithmResult DFS::solve() {
    if (m_result.state != AlgorithmState::kRunning && m_result.state != AlgorithmState::kReady) {
        return m_result;
    }
    algorithmStateChange(AlgorithmState::kRunning);

    auto start = std::chrono::high_resolution_clock::now();

    while (!m_nodes_to_process_stack.empty() && m_result.state == AlgorithmState::kRunning) {
        processNode();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    m_result.time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (m_result.state == AlgorithmState::kPathFound) {
        m_result.path = getPath();
    } else {
        algorithmStateChange(AlgorithmState::kPathNotFound);
    }
    generateStatistics();

    return m_result;
}

AlgorithmResult DFS::step() {
    if (m_result.state != AlgorithmState::kRunning && m_result.state != AlgorithmState::kReady) {
        return m_result;
    }
    algorithmStateChange(AlgorithmState::kRunning);
    if (!m_nodes_to_process_stack.empty() && m_result.state == AlgorithmState::kRunning) {
        processNode();
    }
    if (m_result.state == AlgorithmState::kPathFound) {
        m_result.path = getPath();
    } else if (m_nodes_to_process_stack.empty()) {
        algorithmStateChange(AlgorithmState::kPathNotFound);
    }
    generateStatistics();

    return m_result;
}

void DFS::resetAlgorithm(Grid& grid) {
    m_result.nodes_processed_count = 0;
    m_result.nodes_processed_ratio = 0;
    m_result.path = std::vector<Node>();

    m_grid = grid;
    m_grid.start_node = m_grid.getNodeFromPosition(m_grid.start_node->getPosition());
    m_grid.end_node = m_grid.getNodeFromPosition(m_grid.end_node->getPosition());

    m_nodes_to_process_stack = std::stack<Node*>();
    m_nodes_to_process_stack.push(m_grid.start_node);
}

void DFS::processNode() {
    Node* current_node = m_nodes_to_process_stack.top();
    current_node->setState(NodeState::kProcessed);
    m_result.nodes_processed_count += 1;

    if (current_node->getType() == NodeType::kEnd) {
        algorithmStateChange(AlgorithmState::kPathFound);
        return;
    }
    m_nodes_to_process_stack.pop();
    checkNeightbors(current_node);
}

void DFS::checkNeightbors(Node* current_node) {
    for (int index = 0; index < 4; index++) {
        Position neightbor_position =
            current_node->getPosition() + m_neighbors_check_order.at(index);
        Node* neightbor_node = m_grid.getNodeFromPosition(neightbor_position);

        if (neightbor_node->getState() == NodeState::kUndiscovered &&
            neightbor_node->getType() != NodeType::kWall) {
            neightbor_node->setParent(current_node);
            neightbor_node->setState(NodeState::kDiscovered);
            m_nodes_to_process_stack.push(neightbor_node);
            neightbor_node->setPathWeight(current_node->getPathWeight() +
                                          neightbor_node->getWeight());
        }
    }
}

std::vector<Node> DFS::getPath() {
    if (m_result.state != AlgorithmState::kPathFound) {
        return std::vector<Node>();
    }
    std::vector<Node> path;
    Node* node = m_grid.end_node;
    while (true) {
        path.push_back(*node);
        node = node->getParent();
        if (node == nullptr) {
            break;
        }
    }
    return path;
}

void DFS::algorithmStateChange(AlgorithmState state) {
    if (m_result.state != state) {
        m_result.state = state;
    }
}

void DFS::generateStatistics() {
    m_result.algorithm_type = AlgorithmType::kDFS;
    m_result.nodes_processed_ratio =
        100 * m_result.nodes_processed_count / m_grid.getEmptyNodesCount();
    m_result.grid_resolved = &m_grid;
}
