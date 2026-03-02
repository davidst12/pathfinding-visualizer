#include "Pathfinding/managers/MapManager.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

MapManager::MapManager()
{
}

void MapManager::loadAllMaps(const std::string& folderPath) {
    if (!fs::exists(folderPath)) {
        std::cerr << "Error: La carpeta de mapas no existe." << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".json") {
            loadMap(entry.path().string());
            std::cout << "Mapa cargado: " << entry.path().filename() << std::endl;
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
    
    // Asumiendo que tu Grid tiene un método para setear el tipo de nodo
    for (int y = 0; y < height; ++y) {
        grid_string.push_back(data["data"][y]);
    }

    loadedMaps[name] = Grid(name, grid_string);
    std::cout << "Mapa cargado: " << name << std::endl;
    std::cout << "Mapa cargado: " << loadedMaps[name].toString() << std::endl;
}

std::map<std::string, Grid> MapManager::getAllMaps() { 
    return loadedMaps; 
}