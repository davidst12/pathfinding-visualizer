#include "Pathfinding/managers/MapManager.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

void MapManager::loadAllMaps(const std::string& folderPath) {
    if (!fs::exists(folderPath)) {
        std::cerr << "Error: La carpeta de mapas no existe.\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".json") {
            loadMap(entry.path().string());
        }
    }
}

void MapManager::loadMap(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return;
    }

    json data;
    file >> data;

    std::string name = data["name"];
    int height = static_cast<int>(data["data"].size());
    int width = static_cast<int>(data["data"][0].size());

    std::vector<std::string> grid_string;

    for (int y = 0; y < height; ++y) {
        grid_string.push_back(data["data"][y]);
    }

    m_loaded_maps[name] = Grid(name, grid_string);
}

std::map<std::string, Grid> MapManager::getAllMaps() {
    return m_loaded_maps;
}