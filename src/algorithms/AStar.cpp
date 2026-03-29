#include "Pathfinding/algorithms/AStar.hpp"

#include "Pathfinding/player/AlgorithmPreparation.hpp"

AStar::AStar() {}

bool AStar::prepare(Grid& grid) {
    resetAlgorithm(grid);
    algorithmStateChange(AlgorithmState::kReady);

    return true;
}

AlgorithmResult AStar::solve() {
    if (m_result.state != AlgorithmState::kRunning && m_result.state != AlgorithmState::kReady) {
        return m_result;
    }
    algorithmStateChange(AlgorithmState::kRunning);

    auto start = std::chrono::high_resolution_clock::now();

    while (!m_priority_node_queue.empty() && m_result.state == AlgorithmState::kRunning) {
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

AlgorithmResult AStar::step() {
    if (m_result.state != AlgorithmState::kRunning && m_result.state != AlgorithmState::kReady) {
        return m_result;
    }
    algorithmStateChange(AlgorithmState::kRunning);
    if (!m_priority_node_queue.empty() && m_result.state == AlgorithmState::kRunning) {
        processNode();
    }
    if (m_result.state == AlgorithmState::kPathFound) {
        m_result.path = getPath();
    } else if (m_priority_node_queue.empty()) {
        algorithmStateChange(AlgorithmState::kPathNotFound);
    }
    generateStatistics();

    return m_result;
}

void AStar::resetAlgorithm(Grid& grid) {
    m_result.nodes_processed_count = 0;
    m_result.nodes_processed_ratio = 0;
    m_result.path = std::vector<Node>();

    m_grid = grid;
    m_grid.start_node = m_grid.getNodeFromPosition(m_grid.start_node->getPosition());
    m_grid.end_node = m_grid.getNodeFromPosition(m_grid.end_node->getPosition());
    m_grid.start_node->setCostToEnd(0);

    m_priority_node_queue = std::priority_queue<Node*, std::vector<Node*>, CompareNodes>();
    m_priority_node_queue.push(m_grid.start_node);
}

void AStar::processNode() {
    Node* current_node = m_priority_node_queue.top();
    current_node->setState(NodeState::kProcessed);
    m_result.nodes_processed_count += 1;

    if (current_node->getType() == NodeType::kEnd) {
        algorithmStateChange(AlgorithmState::kPathFound);
        return;
    }
    m_priority_node_queue.pop();
    checkNeightbors(current_node);
}

void AStar::checkNeightbors(Node* current_node) {
    for (int index = 0; index < 4; index++) {
        Position neightbor_position =
            current_node->getPosition() + m_neighbors_check_order.at(index);
        Node* neightbor_node = m_grid.getNodeFromPosition(neightbor_position);

        if (neightbor_node->getType() == NodeType::kWall) {
            continue;
        } else if (neightbor_node->getState() != NodeState::kUndiscovered) {
            int tentative_cost = current_node->getPathWeight() + neightbor_node->getWeight();
            if (tentative_cost >= neightbor_node->getPathWeight()) continue;
        }

        neightbor_node->setPathWeight(current_node->getPathWeight() + neightbor_node->getWeight());
        neightbor_node->setCostToEnd(
            neightbor_node->getPathWeight() +
            heuristic(neightbor_node->getPosition(), m_grid.end_node->getPosition()));
        neightbor_node->setParent(current_node);
        neightbor_node->setState(NodeState::kDiscovered);
        m_priority_node_queue.push(neightbor_node);
    }
}

std::vector<Node> AStar::getPath() {
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

void AStar::algorithmStateChange(AlgorithmState state) {
    if (m_result.state != state) {
        m_result.state = state;
    }
}

void AStar::generateStatistics() {
    m_result.algorithm_type = AlgorithmType::kAStar;
    m_result.nodes_processed_ratio =
        100 * m_result.nodes_processed_count / m_grid.getEmptyNodesCount();
    m_result.grid_resolved = &m_grid;
}

int AStar::heuristic(Position first, Position second) {
    return abs(first.x - second.x) + abs(first.y - second.y);
}
