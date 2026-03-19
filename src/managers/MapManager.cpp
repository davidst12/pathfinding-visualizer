#include "Pathfinding/managers/MapManager.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;


void MapManager::loadAllMaps(const std::string& folderPath) {
    if (!fs::exists(folderPath)) {
        std::cerr << "Error: La carpeta de mapas no existe." << std::endl;
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
    if (!file.is_open()) return;

    json data;
    file >> data;

    std::string name = data["name"];
    int height = data["data"].size();
    int width = data["data"][0].size();

    std::vector<std::string> grid_string;
    
    for (int y = 0; y < height; ++y) {
        grid_string.push_back(data["data"][y]);
    }

    loadedMaps[name] = Grid(name, grid_string);
}

std::map<std::string, Grid> MapManager::getAllMaps() { 
    return loadedMaps; 
}