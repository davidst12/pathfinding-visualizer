#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "Pathfinding/core/Grid.hpp"

class MapManager
{
public:
    MapManager();

    void loadAllMaps(const std::string& folderPath);
    void loadMap(const std::string& filePath);
    std::map<std::string, Grid> getAllMaps();

private:
    std::map<std::string, Grid> loadedMaps;
};